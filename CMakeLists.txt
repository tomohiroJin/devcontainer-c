cmake_minimum_required(VERSION 3.10)

project(BasicVariables)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# ソースコードとテストコードのディレクトリ
set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)
set(TEST_DIR ${CMAKE_SOURCE_DIR}/tests)

# Boost を検索
find_package(Boost REQUIRED)
if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    message(STATUS "Boost found: ${Boost_INCLUDE_DIRS}")
else()
    message(FATAL_ERROR "Boost not found!")
endif()

# GoogleTest を検索
find_package(GTest REQUIRED)
if(GTest_FOUND)
    include_directories(${GTEST_INCLUDE_DIRS})
    message(STATUS "GoogleTest found: ${GTEST_INCLUDE_DIRS}")
else()
    message(FATAL_ERROR "GoogleTest not found!")
endif()

# src をインクルードパスに追加
include_directories(${SRC_DIR})

# src 以下の全ての cpp ファイルをライブラリに追加
file(GLOB_RECURSE SRC_FILES ${SRC_DIR}/*.cpp)
add_library(basic_variables ${SRC_FILES})

# tests/main.cpp を作成する
set(TEST_MAIN ${TEST_DIR}/main.cpp)
file(WRITE ${TEST_MAIN} "
#include <gtest/gtest.h>
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}")

# tests 以下の全てのテスト cpp ファイルを対象にする
file(GLOB_RECURSE TEST_FILES ${TEST_DIR}/*.cpp)

# テスト実行ファイルを作成
add_executable(test_runner ${TEST_MAIN} ${TEST_FILES})
target_link_libraries(test_runner PRIVATE basic_variables GTest::GTest GTest::Main pthread ${Boost_LIBRARIES})

# CTest にテストを登録
enable_testing()
include(GoogleTest)
gtest_discover_tests(test_runner)
