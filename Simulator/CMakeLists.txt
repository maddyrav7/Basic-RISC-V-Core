cmake_minimum_required(VERSION 3.12.0)
project(brvc_sim VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(GLOBAL PROPERTY USE_FOLDERS ON)


if (MSVC)
    add_compile_options(
        /W4
        /WX
    )
else()
    message(FATAL_ERROR "This project only supports MSVC.")
endif()

add_subdirectory(src)
add_subdirectory(test/src)