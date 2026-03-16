cmake_minimum_required(VERSION 3.16)

project(hello LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenCV REQUIRED)

add_executable(hello src/main.cpp)
target_link_libraries(hello PRIVATE ${OpenCV_LIBS})
target_include_directories(hello PRIVATE ${OpenCV_INCLUDE_DIRS})

file(GLOB EXERCISE_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/exercises/*.cpp")

foreach(ex_src IN LISTS EXERCISE_SOURCES)
    get_filename_component(ex_name ${ex_src} NAME_WE)
    string(REPLACE "." "_" ex_name "${ex_name}")
    set(target_name "ex_${ex_name}")

    add_executable(${target_name} ${ex_src})
    target_link_libraries(${target_name} PRIVATE ${OpenCV_LIBS})
    target_include_directories(${target_name} PRIVATE ${OpenCV_INCLUDE_DIRS})
endforeach()
