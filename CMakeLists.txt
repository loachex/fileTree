#cmake最小版本设置
cmake_minimum_required(VERSION 3.0)
#项目名称
project(imgTree)
#添加宏：DEBUG
add_definitions(-DDEBUG)
#包含头文件库
include_directories(./include)
#添加源文件
aux_source_directory(./src/main SRCS)
aux_source_directory(./src/tree SRCS)
#build
add_executable(imgTree ${SRCS})
