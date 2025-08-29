cmake_minimum_required(VERSION 3.15)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(AngelEngine LANGUAGES CXX)

set(add_on
    external/angelscript/add_on/scriptstdstring/scriptstdstring.cpp
    external/angelscript/add_on/scriptstdstring/scriptstdstring.h
    external/angelscript/add_on/scriptstdstring/scriptstdstring_utils.cpp
    external/angelscript/add_on/scriptbuilder/scriptbuilder.h
    external/angelscript/add_on/scriptbuilder/scriptbuilder.cpp
    external/angelscript/add_on/scriptarray/scriptarray.cpp
)

set(Source
    source/headers/AngelEngine.hpp
    source/src/AngelEngine.cpp
)

find_package(fmt CONFIG REQUIRED)

find_package(Angelscript CONFIG REQUIRED)

add_executable(${PROJECT_NAME} "source/main.cpp" ${Source} ${add_on})

target_include_directories(${PROJECT_NAME}
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/source/headers        # Headers públicos
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/source/src            # Headers privados
)

target_include_directories(${PROJECT_NAME} PRIVATE "external/angelscript/add_on/")

target_link_libraries(${PROJECT_NAME} fmt::fmt Angelscript::angelscript )

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
