cmake_minimum_required(VERSION 3.0.0)
project(arrayQueue)

set(ARRAYQUEUEFOLDER ${PROJECT_SOURCE_DIR}/arrayQueue)
set(LINEARTABLE ${PROJECT_SOURCE_DIR}/Lineartable)
set(MATRIX ${PROJECT_SOURCE_DIR}/Matrix)
set(STACK ${PROJECT_SOURCE_DIR}/Stack)

include_directories(${ARRAYQUEUEFOLDER} ${LINEARTABLE} ${MATRIX} ${STACK})

add_executable(arrayQueue main.cpp)





