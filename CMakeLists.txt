# policygen compiler instrction
cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

project(PPACK LANGUAGES CXX)
set(CMAKE_CXX_FLAGS "-fpermissive")

# adding mask library
add_library(mask
  STATIC
  "include/mask.hpp"
  "src/mask.cpp")

add_library(ppack
  STATIC
  "include/ppack.hpp"
  "src/ppack.cpp")


# create the policygen executable
add_executable(policygen "src/policygen.cpp")


# link with mask  dependences
target_link_libraries(policygen mask)

# link with ppack  dependences
target_link_libraries(policygen ppack)
