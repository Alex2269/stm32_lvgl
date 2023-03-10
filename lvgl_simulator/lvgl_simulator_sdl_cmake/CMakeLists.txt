cmake_minimum_required(VERSION 3.10)
project(lvgl)
set(CMAKE_C_STANDARD 11)#C11
set(CMAKE_CXX_STANDARD 17)#C17
set(CMAKE_CXX_STANDARD_REQUIRED ON)

INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR})

file(GLOB_RECURSE allheader RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "*.h")
# file(GLOB_RECURSE allsource RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "*.c")
file(GLOB_RECURSE allsource RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
    "lv_drivers/*.c"
    "lv_demos/*.c"
    "lvgl/*.c"
    "main/*.c"
    "my_proj/*.c"
)

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin) 
SET(CMAKE_CXX_FLAGS "-O3")

find_package(SDL2 REQUIRED SDL2)
include_directories(${SDL2_INCLUDE_DIRS})
add_executable(sim ${allsource} ${allheader})
add_compile_definitions(LV_CONF_INCLUDE_SIMPLE)
target_link_libraries(sim PRIVATE SDL2 )
add_custom_target (run COMMAND ${EXECUTABLE_OUTPUT_PATH}/sim)
