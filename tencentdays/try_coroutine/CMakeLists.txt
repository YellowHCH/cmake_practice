#set(CXX_FLAGS -Wall -o -lpthread -pthread)
# 设置库文件输出路径
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)
# 设置当前项目的头文件搜索路径
include_directories(./include)
# 添加源代码路径
aux_source_directory(./src DIR_LIB_SRCS)
# 生成库文件
add_library(coroutine_try SHARED ${DIR_LIB_SRCS})
# 要添加线程库的链接
target_link_libraries(coroutine_try ${CMAKE_THREAD_LIBS_INIT})
