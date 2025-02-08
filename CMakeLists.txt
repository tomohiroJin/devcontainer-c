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

# src 以下の全ての cpp ファイルを対象にする
file(GLOB_RECURSE SRC_FILES ${SRC_DIR}/*.cpp)
add_library(basic_variables ${SRC_FILES})

# tests 以下の全てのテスト cpp ファイルを対象にする
file(GLOB_RECURSE TEST_FILES ${TEST_DIR}/*.cpp)
foreach(TEST_FILE ${TEST_FILES})
    include_directories(${SRC_DIR})
    get_filename_component(TEST_NAME ${TEST_FILE} NAME_WE)
    add_executable(${TEST_NAME} ${TEST_FILE})
    target_link_libraries(${TEST_NAME} basic_variables ${GTEST_LIBRARIES} gtest_main pthread ${Boost_LIBRARIES})
    add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})
endforeach()

# 実行可能ファイルの追加 (オプション: 実装の確認用)
file(GLOB_RECURSE EXEC_FILES ${SRC_DIR}/basic/main.cpp)
if(EXEC_FILES)
    add_executable(basic_app ${EXEC_FILES})
    target_link_libraries(basic_app basic_variables ${Boost_LIBRARIES})
endif()

enable_testing()
