cmake_minimum_required(VERSION 3.21.2)

project(Cognizant LANGUAGES CXX)

enable_testing()
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_subdirectory(source)
add_subdirectory(tests)

add_executable(${PROJECT_NAME} main.cpp)

target_precompile_headers(${PROJECT_NAME} PRIVATE source/utils/pch.h)
target_link_libraries(${PROJECT_NAME} PRIVATE search)
