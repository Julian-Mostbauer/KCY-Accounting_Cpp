cmake_minimum_required(VERSION 4.0)
project(LicenseServer)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

add_executable(license_server
        src/main.cpp
        lib/License.cpp
        lib/License.h
        lib/LicenseServer.cpp
        lib/LicenseServer.h
)

add_executable(license_tests
        tests/test_license.cpp
        lib/License.cpp
        tests/catch.cpp
)

target_include_directories(license_tests PRIVATE lib)