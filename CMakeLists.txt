cmake_minimum_required(VERSION 2.8.9)
project (distributed_particle_filter)

include_directories(include)

add_custom_command(
  OUTPUT ztable_data.c
  COMMAND ../bin/ztable_gen
  DEPENDS bin/ztable_gen
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
)

file(GLOB PROBABILITY_SOURCES "src/probability/*.c")
add_library(probability ${PROBABILITY_SOURCES} ztable_data.c)

file(GLOB UTILS_SOURCES "src/utils/*.c")
add_library(utils ${UTILS_SOURCES})

file(GLOB VECTOR_SOURCES "src/vector/*.c")
add_library(vector ${VECTOR_SOURCES})

file(GLOB PARTICLE_FILTER_SOURCES "src/particle_filter/*.c")
add_library(particle_filter ${PARTICLE_FILTER_SOURCES})

file(GLOB TRILITERATION_SOURCES "src/triliteration/*.c")
add_library(triliteration ${TRILITERATION_SOURCES})

