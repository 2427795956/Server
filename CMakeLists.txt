# CMake 最低版本号要求
cmake_minimum_required (VERSION 2.8)
# 项目信息
project (Test)

# 查找当前目录下的所有源文件
# 并将名称保存到 DIR_SRCS 变量
aux_source_directory(. DIR_SRCS)
# 添加 math 子目录
add_subdirectory(base)
# 指定生成目标 
add_executable(Server main.cpp EventLoop.cpp Channel.cpp Epoll.cpp Timer.cpp 
EventLoopThread.cpp Server.cpp Connection.cpp EventLoopThreadPool.cpp 
HttpServer.cpp AsyncLogging.cpp FileUtil.cpp LogFile.cpp LogStream.cpp Logging.cpp)
# 添加链接库
target_link_libraries(Server Base)

#添加调试信息
SET(CMAKE_BUILD_TYPE "Debug")
SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g2 -ggdb")
SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")



