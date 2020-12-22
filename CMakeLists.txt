cmake_minimum_required(VERSION 3.0)

project(imgTree)

include_directories(./include)

aux_source_directory(./src/main SRCS)
aux_source_directory(./src/tree SRCS)

add_executable(imgTree ${SRCS})
