cmake_minimum_required(VERSION 3.11.0 FATAL_ERROR)

find_package(gz-cmake3 REQUIRED)

project(DummySensorSystem)

gz_find_package(gz-plugin2 REQUIRED COMPONENTS register)
set(GZ_PLUGIN_VER ${gz-plugin2_VERSION_MAJOR})

gz_find_package(gz-sim8 REQUIRED)
set(GZ_SIM_VER ${gz-sim8_VERSION_MAJOR})

find_package(gz-sensors8 REQUIRED)
set(GZ_SENSORS_VER ${gz-sensors8_VERSION_MAJOR})

# First, create the sensor library
add_library(dummysensor SHARED DummySensor.cc)
target_link_libraries(dummysensor
  PUBLIC gz-sensors${GZ_SENSORS_VER}::gz-sensors${GZ_SENSORS_VER})

# Then, create the system plugin that integrates with Gazebo
add_library(${PROJECT_NAME} SHARED DummySensorSystem.cc)
target_link_libraries(${PROJECT_NAME}
  PRIVATE
    gz-plugin${GZ_PLUGIN_VER}::gz-plugin${GZ_PLUGIN_VER}
    gz-sim${GZ_SIM_VER}::gz-sim${GZ_SIM_VER}
    gz-sensors${GZ_SENSORS_VER}::gz-sensors${GZ_SENSORS_VER}
    dummysensor
)