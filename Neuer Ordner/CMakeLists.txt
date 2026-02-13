add_library(sentinex-core STATIC
  src/bicycle_motion.cpp
  src/vehicle_state.cpp
  # add more core .cpp files here
)

target_include_directories(sentinex-core PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/include
)
