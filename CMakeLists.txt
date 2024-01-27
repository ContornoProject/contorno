cmake_minimum_required(VERSION 3.0)
project(contorno)

if (!WIN32)
    set(CMAKE_C_FLAGS "-fms-extensions -g -fvisibility=hidden -fPIC")
endif()

file(GLOB CONTORNO_SOURCE_FILES src/*.c)

include_directories("include")

add_library(contorno SHARED ${CONTORNO_SOURCE_FILES})
set_target_properties(contorno PROPERTIES LINKER_LANGUAGE C)
set_target_properties(contorno PROPERTIES OUTPUT_NAME libcontorno)

