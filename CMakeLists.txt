cmake_minimum_required(VERSION 3.0.0)
project(arrayQueue)

set(ARRAYQUEUEFOLDER ${PROJECT_SOURCE_DIR}/arrayQueue)

include_directories(${ARRAYQUEUEFOLDER})

add_executable(arrayQueue main.cpp)


