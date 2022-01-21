cmake_minimum_required(VERSION 3.0.0)
project(arrayQueue)

set(ARRAYQUEUEFOLDER ${PROJECT_SOURCE_DIR}/arrayQueue)
set(LINEARTABLE ${PROJECT_SOURCE_DIR}/Lineartable)
set(MATRIX ${PROJECT_SOURCE_DIR}/Matrix)
set(STACK ${PROJECT_SOURCE_DIR}/Stack)
set(AA ${PROJECT_SOURCE_DIR}/aa)

add_subdirectory(Lineartable)
add_subdirectory(Matrix)
add_subdirectory(aa)

include_directories(${ARRAYQUEUEFOLDER} ${LINEARTABLE} ${MATRIX} ${STACK} ${AA})

add_executable(arrayQueue main.cpp)

target_link_libraries(arrayQueue Lineartable)

target_link_libraries(arrayQueue Matrix)

target_link_libraries(arrayQueue aa)




