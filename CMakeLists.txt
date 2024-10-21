cmake_minimum_required(VERSION 3.8)

project(knn_cpp)

# 设置全局的C++标准
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 添加可执行文件，只包含 main.cpp
add_executable(knn_cpp "main.cpp")
