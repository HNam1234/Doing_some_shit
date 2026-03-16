cmake_minimum_required(VERSION 3.16)

project(hello LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenCV REQUIRED)

add_executable(hello src/main.cpp)

target_link_libraries(hello PRIVATE ${OpenCV_LIBS})
target_include_directories(hello PRIVATE ${OpenCV_INCLUDE_DIRS})