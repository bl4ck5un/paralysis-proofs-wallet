add_definitions(-DIN_ENCLAVE -DSGX)

######################
# Build Dependencies #
######################

set(secp256k1_PREFIX ${CMAKE_CURRENT_SOURCE_DIR}/secp256k1)
set(secp256k1_LIB ${secp256k1_PREFIX}/lib/libsecp256k1.a)
set(secp256k1_INCLUDE ${secp256k1_PREFIX}/include)

# for secp256k1
include(ExternalProject)
ExternalProject_Add(secp256k1-enclave
        GIT_REPOSITORY https://github.com/bl4ck5un/secp256k1-sgx
        UPDATE_COMMAND ""
        CONFIGURE_COMMAND cd sgx/ && ./autogen.sh && env CPPFLAGS=-fPIC ./configure
        --enable-shared
        --enable-endomorphism
        --enable-module-recovery
        --enable-benchmark=no
        --enable-module-ecdh=no
        --enable-ecmult-static-precomputation=no
        --enable-coverage=no
        --enable-tests=no
        --enable-openssl-tests=no
        --enable-exhaustive-tests=no
        --with-bignum=no
        --prefix ${secp256k1_PREFIX}
        BUILD_COMMAND cd sgx/ && make -j
        BUILD_IN_SOURCE true
        INSTALL_COMMAND cd sgx/ && make install
        )

add_custom_command(
        OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/Enclave_t.c ${CMAKE_CURRENT_BINARY_DIR}/Enclave_t.h
        COMMAND ${SGX_EDGER8R} --trusted ${CMAKE_SOURCE_DIR}/common/Enclave.edl
        --search-path ${SGX_SDK}/include
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
)

#####################
# Build the Enclave #
#####################

FILE(GLOB BITCOIN_SRC_FILES "bitcoin/*.cpp")
set(BITCOIN_SRC_FILES
        ${BITCOIN_SRC_FILES}
        bitcoin/primitives/block.cpp
        bitcoin/primitives/transaction.cpp
        bitcoin/crypto/sha1.cpp
        bitcoin/crypto/sha256.cpp
        bitcoin/crypto/sha512.cpp
        bitcoin/crypto/ripemd160.cpp
        bitcoin/crypto/hmac_sha512.cpp
        bitcoin/script/interpreter.cpp
        bitcoin/script/script.cpp
        bitcoin/script/script_error.cpp
        bitcoin/script/sign.cpp
        bitcoin/script/standard.cpp)

set(ENCLAVE_SOURCE_FILES
        Enclave_t.c
        ../common/message.c
        log.cpp
        pprint.cpp
        utils.cpp
        paralysis.cpp
        bitcoin_helpers.cpp
        ecalls.cpp
        ${BITCOIN_SRC_FILES})

add_library(enclave SHARED ${ENCLAVE_SOURCE_FILES})

# set compliation flags
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${SGX_COMMON_CFLAGS} -Wall -Wno-deprecated -nostdinc -fvisibility=hidden -fpie -fstack-protector")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CMAKE_C_FLAGS} -std=c++11 -nostdinc++")

# set complication parameters
include_directories(
        ${CMAKE_CURRENT_BINARY_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${SGX_SDK}/include
        ${SGX_SDK}/include/tlibc
        ${SGX_SDK}/include/libcxx
        ${MBEDTLS_SGX_ROOT_DIR}/include
        ${CMAKE_SOURCE_DIR}/common
        bitcoin
        nacl
        ${secp256k1_INCLUDE}
)


set_target_properties(enclave PROPERTIES PREFIX "")

set_directory_properties(PROPERTIES
        ADDITIONAL_MAKE_CLEAN_FILES Enclave_t.c
        ADDITIONAL_MAKE_CLEAN_FILES Enclave_t.h)

target_link_libraries(enclave "${SGX_COMMON_CFLAGS} \
    -Wl,--no-undefined -nostdlib -nodefaultlibs -nostartfiles -L${SGX_LIBRARY_PATH} \
    -Wl,--whole-archive -l${SGX_TRTS_LIB} -Wl,--no-whole-archive \
    -Wl,--start-group \
        -lsgx_tstdc -lsgx_tcxx -lsgx_tcrypto -l${SGX_TSVC_LIB} ${secp256k1_LIB}\
    -Wl,--end-group \
    -Wl,-Bstatic -Wl,-Bsymbolic -Wl,--no-undefined \
    -Wl,-pie,-eenclave_entry -Wl,--export-dynamic \
    -Wl,--defsym,__ImageBase=0")

# sign the enclave
add_custom_command(TARGET enclave
        POST_BUILD
        COMMAND ${SGX_ENCLAVE_SIGNER} sign
        -key Enclave_private.pem
        -config Enclave.config.xml
        -enclave ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/enclave.so
        -out ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/enclave.signed.so
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        COMMENT "Signing the enclave. Writing to ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}")

add_dependencies(enclave secp256k1-enclave)
