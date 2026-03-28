cmake_minimum_required(VERSION 4.0)

project(MGEngineTests)

set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

enable_testing()
find_package(GTest CONFIG REQUIRED)

add_executable(MGEngineTests example_test.cpp
        Utils/FastRefList_test.cpp)
target_link_libraries(MGEngineTests PRIVATE GTest::gtest GTest::gtest_main GTest::gmock GTest::gmock_main MGEngineLib)
target_include_directories(MGEngineTests PRIVATE ${PROJECT_SOURCE_DIR}/MGEngine)

include(GoogleTest)
gtest_discover_tests(MGEngineTests)
