
# 设置项目名
project(project_name)
# 设置最低cmake版本
cmake_minimum_required(VERSION 2.8)
set(CMAKE_BUILD_TYPE "Release")
# 设置编译器
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
#set(CMAKE_CXX_COMPILER "g++-7")
add_compile_options(-std=c++11)

set(CXX_FLAGS -Wall -o -lpthread -pthread)
# 要使用多线程库thread需要添加线程库的包
find_package(Threads)

# 设置可执行文件输出位置
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
# 设置源代码位置
aux_source_directory(./src DIR_SRCS)
# 设置当前项目的头文件搜索路径
include_directories(./include ./sub1/include)

# 添加子目录
add_subdirectory(sub1)

# 生成可执行文件
add_executable(exe_name ${DIR_SRCS})
# 设置链接库
target_link_libraries(exe_name subLib)