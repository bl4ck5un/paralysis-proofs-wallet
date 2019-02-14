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

set(CMAKE_PREFIX_PATH /opt/Qt/5.12.1/gcc_64)

# Instruct CMake to run moc automatically when needed
set(CMAKE_AUTOMOC ON)
# Create code from a list of Qt designer ui files
set(CMAKE_AUTOUIC ON)

add_executable(pp
        ../common/message.c
        main.cpp
        pp.ui
        enclave-utils.cpp
        interrupt.cpp
        Enclave_u.c
        ui.cpp
        wallet.cpp)

find_package(Qt5 COMPONENTS Widgets REQUIRED)

find_package(Boost REQUIRED COMPONENTS program_options filesystem)
find_package(Log4CXX REQUIRED)

#find_package(Qt5 COMPONENTS Widgets Qml Quick REQUIRED)

include_directories(
        Qt5::Widgets
        Boost::program_options
        ${LOG4CXX_INCLUDE_DIR}
        ${SGXSDK_INCLUDE_DIRS}
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_BINARY_DIR}
)

target_link_libraries(pp
        Qt5::Widgets
        Boost::program_options
        Boost::filesystem
        ${LOG4CXX_LIBRARY}
        -L${SGX_LIBRARY_PATH} -l${SGX_URTS_LIB} -l${SGX_USVC_LIB}
        -lpthread
        )

add_dependencies(pp enclave)

add_custom_command(TARGET pp
        POST_BUILD
        COMMAND cp -f ${CMAKE_CURRENT_SOURCE_DIR}/logging.conf
        ${CMAKE_SOURCE_DIR}/example-wallet.json
        ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
        COMMENT "Installing the configuration files")
