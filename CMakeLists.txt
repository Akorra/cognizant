cmake_minimum_required(VERSION 3.21.2)

project(Cognizant LANGUAGES CXX)

enable_testing()
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_subdirectory(source)
add_subdirectory(tests)

add_executable(${PROJECT_NAME} main.cpp)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE Threads::Threads)

target_precompile_headers(${PROJECT_NAME} PRIVATE source/utils/pch.h)
target_link_libraries(${PROJECT_NAME} PRIVATE search)
target_link_libraries(${PROJECT_NAME} PRIVATE profiling)
