cmake_minimum_required(VERSION 3.10.2 FATAL_ERROR)

project(dummysensor)

find_package(gz-cmake3 REQUIRED)
find_package(gz-sensors8 REQUIRED)

add_library(${PROJECT_NAME} SHARED DummySensor.cc)
target_link_libraries(${PROJECT_NAME}
  PUBLIC gz-sensors8::gz-sensors8)