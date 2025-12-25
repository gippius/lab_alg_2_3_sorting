cmake_minimum_required(VERSION 3.16)
project(lab_2_3_sorting LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if (MSVC)
    add_compile_options(/W4 /utf-8)
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

add_library(ds
        ${SRC_DIR}/ds/sort.cpp
)
target_include_directories(ds PUBLIC ${SRC_DIR})

add_library(app
        ${SRC_DIR}/app/menu.cpp
)
target_link_libraries(app PRIVATE ds)
target_include_directories(app PUBLIC ${SRC_DIR})

add_executable(lab_2_3_sorting
        ${SRC_DIR}/app/main.cpp
)
target_link_libraries(lab_2_3_sorting PRIVATE app)

set_target_properties(lab_2_3_sorting PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
)
