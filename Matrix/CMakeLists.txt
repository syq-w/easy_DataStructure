project(Matrix)

aux_source_directory(${PROJECT_SOURCE_DIR} Li1)

include_directories(${PROJECT_SOURCE_DIR})

add_library(${PROJECT_NAME} STATIC ${Li1})