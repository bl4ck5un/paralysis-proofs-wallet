set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${SGX_COMMON_CFLAGS} -fPIC -Wall -Wno-sign-compare -Wno-deprecated")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CMAKE_C_FLAGS} -std=c++11")

set_directory_properties(PROPERTIES
        ADDITIONAL_MAKE_CLEAN_FILES Enclave_u.c
        ADDITIONAL_MAKE_CLEAN_FILES Enclave_u.h)

add_custom_command(
        OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/Enclave_u.c ${CMAKE_CURRENT_BINARY_DIR}/Enclave_u.h
        COMMAND ${SGX_EDGER8R} --untrusted Enclave.edl
        --search-path ${CMAKE_SOURCE_DIR}/common
        --search-path ${SGX_SDK}/include
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
)

add_executable(pp
        main.cpp
        bitcoind-rpc.cpp
        Utils.cpp
        interrupt.cpp
        Enclave_u.c
        ${BRIDGE_SRC})

find_package(Jsoncpp REQUIRED)
find_package(JsonCppRpc REQUIRED)
find_package(CURL REQUIRED)
find_package(Boost REQUIRED COMPONENTS program_options filesystem thread)
find_package(OpenSSL REQUIRED)
find_package(Log4CXX REQUIRED)

include_directories(
        ${CURL_INCLUDE_DIRS}
        ${JSONCPP_INCLUDE_DIRS}/${JSONCPP_INCLUDE_PREFIX}
        ${JSONRPCCPP_INCLUDE_DIRS}
        ${SGXSDK_INCLUDE_DIRS}
        ${Boost_INCLUDE_DIRS}
        ${OPENSSL_INCLUDE_DIR}
        ${LOG4CXX_INCLUDE_DIR}
        ${CMAKE_CURRENT_BINARY_DIR}
)

set(RPC_LIB_BUNDLE
        ${CURL_LIBRARIES}
        ${JSONCPP_LIBRARIES}
        ${JSONRPCCPP_LIBRARIES}
        )

set(COMMON_LIBS
        ${LOG4CXX_LIBRARY}
        )

target_link_libraries(pp
        ${RPC_LIB_BUNDLE}
        ${COMMON_LIBS}
        ${Boost_LIBRARIES}
        ${LOG4CXX_LIBRARY}
        ${OPENSSL_CRYPTO_LIBRARY}
        -L${SGX_LIBRARY_PATH} -l${SGX_URTS_LIB} -l${SGX_USVC_LIB}
        -lpthread
        )

add_dependencies(pp enclave)

add_custom_command(TARGET pp
        POST_BUILD
        COMMAND cp -f ${CMAKE_CURRENT_SOURCE_DIR}/logging.conf
        ${CMAKE_SOURCE_DIR}/config.toml
        ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
        COMMENT "Installing the configuration files")
