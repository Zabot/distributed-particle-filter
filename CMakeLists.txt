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
add_library(probability SHARED ${PROBABILITY_SOURCES} ztable_data.c)

file(GLOB UTILS_SOURCES "src/utils/*.c")
add_library(utils SHARED ${UTILS_SOURCES})

file(GLOB VECTOR_SOURCES "src/vector/*.c")
add_library(vector SHARED ${VECTOR_SOURCES})
target_link_libraries(vector utils)

file(GLOB PARTICLE_FILTER_SOURCES "src/particle_filter/*.c")
add_library(particle_filter SHARED ${PARTICLE_FILTER_SOURCES})
target_link_libraries(particle_filter utils vector)

file(GLOB TRILITERATION_SOURCES "src/triliteration/*.c")
add_library(triliteration SHARED ${TRILITERATION_SOURCES})
target_link_libraries(triliteration probability vector)

file(GLOB VISUALIZATION_SOURCES "src/visualization/*.c")
add_library(visualization SHARED ${VISUALIZATION_SOURCES})
target_link_libraries(visualization vector SDL2 particle_filter triliteration)

file(GLOB SINGLE_NODE_TEST_SOURCES "src/single_node_test/*.c")
add_executable(single_node_test ${SINGLE_NODE_TEST_SOURCES})
target_link_libraries(single_node_test SDL2 m probability utils vector visualization particle_filter triliteration visualization)

file(GLOB SIMULATION_SOURCES "src/simulate/*.c")
add_library(simulation ${SIMULATION_SOURCES})
set_property(TARGET simulation PROPERTY POSITION_INDEPENDENT_CODE ON)
target_link_libraries(simulation vector)

