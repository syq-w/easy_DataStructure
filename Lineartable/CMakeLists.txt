#cmake_minimum_required(VERSION 3.0.0)
project(Lineartable)

aux_source_directory(${PROJECT_SOURCE_DIR} Li)

include_directories(${PROJECT_SOURCE_DIR})

add_library(${PROJECT_NAME} STATIC ${Li})



