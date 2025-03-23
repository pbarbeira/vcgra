cmake_minimum_required(VERSION 3.28)
project(src/vcgra)

set(CMAKE_CXX_STANDARD 26)

enable_testing()

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/heads/main.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(run_tests
        test/test_main.cpp
)

target_link_libraries(run_tests gtest gtest_main)

add_executable(vcgra src/main.cpp)
