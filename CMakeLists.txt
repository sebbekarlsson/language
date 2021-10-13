cmake_minimum_required(VERSION 3.20)

project(language)

add_compile_options(-g -Wall)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

file(GLOB sourcefiles ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)

add_executable(language ${sourcefiles})
