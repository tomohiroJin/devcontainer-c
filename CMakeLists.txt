cmake_minimum_required(VERSION 3.10)
project(MyProject)

# C++ 標準を指定
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

# 実装用ライブラリ
add_library(my_library
    ${SRC_DIR}/math.cpp
)

# テストの設定
enable_testing()

# テスト実行可能ファイル
add_executable(math_test
    ${TEST_DIR}/math_test.cpp
)

# テストにライブラリと必要な依存関係をリンク
target_link_libraries(math_test
    my_library
    ${GTEST_LIBRARIES}
    gtest_main
    pthread
    ${Boost_LIBRARIES}
)

# 実行可能ファイルの追加 (オプション: 実装の確認用)
add_executable(my_app
    ${SRC_DIR}/main.cpp
)

# 実行ファイルにライブラリと Boost をリンク
target_link_libraries(my_app
    my_library
    ${Boost_LIBRARIES}
)

# テストの登録
add_test(NAME MathTests COMMAND math_test)

