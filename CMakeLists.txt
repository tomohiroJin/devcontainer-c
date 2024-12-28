set(GTEST_ROOT /usr) # GoogleTest のルートディレクトリを指定
set(GTEST_INCLUDE_DIRS ${GTEST_ROOT}/include)
set(GTEST_LIBRARIES ${GTEST_ROOT}/lib/libgtest.a ${GTEST_ROOT}/lib/libgtest_main.a)

cmake_minimum_required(VERSION 3.10)
project(MyProject)

# C++ 標準の設定
set(CMAKE_CXX_STANDARD 17)

# src ディレクトリの設定
add_library(math src/math.cpp)

# テストの設定
enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(math_test tests/math_test.cpp)
target_link_libraries(math_test math ${GTEST_LIBRARIES} pthread)

# テストを自動実行
add_test(NAME MathTests COMMAND math_test)

add_executable(my_app src/main.cpp)
target_link_libraries(my_app math)
