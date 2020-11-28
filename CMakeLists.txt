cmake_minimum_required(VERSION 3.5)

project(BufferCache LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(BufferCache main.cpp buffercache.cpp)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(BufferCache PRIVATE Threads::Threads)
