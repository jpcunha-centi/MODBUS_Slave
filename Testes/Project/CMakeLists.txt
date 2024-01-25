cmake_minimum_required(VERSION 3.20.0)

project(CeNTI_Library)

add_library(centi_library STATIC)

target_include_directories(centi_library PRIVATE .)

add_subdirectory(CeNTI_HAL)
add_subdirectory(CeNTI_lib)
