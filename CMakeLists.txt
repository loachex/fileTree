#cmake最小版本设置
cmake_minimum_required(VERSION 3.0)
#项目名称
project(fileTree)
#添加宏：DEBUG
#add_definitions(-DDEBUG)
#包含头文件库
find_package(OpenCV REQUIRED)
set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -march=native -O3 -pthread" )
include_directories(./include)
#添加源文件
aux_source_directory(./src/main SRCS)
aux_source_directory(./src/tree SRCS)
#build
add_executable(fileTree ${SRCS})
target_link_libraries(fileTree PRIVATE ${OpenCV_LIBS})

