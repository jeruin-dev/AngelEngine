cmake_minimum_required(VERSION 3.15)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(AngelEngine LANGUAGES CXX)

find_package(fmt CONFIG REQUIRED)

find_package(Angelscript CONFIG REQUIRED)

add_executable(${PROJECT_NAME} "main.cpp")

target_link_libraries(${PROJECT_NAME} fmt::fmt Angelscript::angelscript)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
