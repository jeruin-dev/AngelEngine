cmake_minimum_required(VERSION 3.15)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(AngelEngine LANGUAGES CXX)



find_package(fmt CONFIG REQUIRED)

add_executable(${PROJECT_NAME} "main.cpp")

target_include_directories(${PROJECT_NAME} PRIVATE ${fmt_INCLUDE_DIRS})

target_link_libraries(${PROJECT_NAME} fmt::fmt)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
