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

add_executable(vcgra src/main.cpp
        src/vcgra/VCGRA.h
        src/vcgra/CycleCounter.h
        src/vcgra/VCGRAConfig.h
        src/vcgra/ProcessingUnit.h
        src/json-parse/JsonNode.h
        src/json-parse/JsonParser.h
        src/json-parse/Lexer.h
        src/json-parse/Token.h
        src/tree-loader/Instance.h
        src/tree-loader/Node.h
        src/tree-loader/TreeLoader.h
        src/tree-loader/TypeConverter.h
)
