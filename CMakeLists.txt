cmake_minimum_required(VERSION 3.20)

project(BasicVariables CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_EXTENSIONS OFF)

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
# NOTE: GLOB_RECURSE を使用しているため、ファイル追加・削除後は再度 cmake を実行すること
file(GLOB_RECURSE SRC_FILES ${SRC_DIR}/*.cpp)
add_library(basic_variables ${SRC_FILES})

# tests のエントリポイント（実ファイル。動的生成はしない）
set(TEST_MAIN ${TEST_DIR}/main.cpp)

# tests 以下の全てのテスト cpp ファイルを対象にする
file(GLOB_RECURSE TEST_FILES ${TEST_DIR}/*.cpp)
# TEST_MAIN は add_executable 側でも追加するため二重追加を避けるためリストから除外
list(REMOVE_ITEM TEST_FILES ${TEST_MAIN})

# テスト実行ファイルを作成
add_executable(test_runner ${TEST_MAIN} ${TEST_FILES})
target_link_libraries(test_runner PRIVATE basic_variables GTest::GTest GTest::Main pthread ${Boost_LIBRARIES})

# CTest にテストを登録
enable_testing()
include(GoogleTest)
gtest_discover_tests(test_runner)
