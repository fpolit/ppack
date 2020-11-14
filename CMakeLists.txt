# policygen compiler instrction
cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

project(PPACK LANGUAGES CXX)
set(CMAKE_CXX_FLAGS "-fpermissive")

# adding mask library
add_library(mask
  STATIC
  "include/mask.hpp"
  "src/mask.cpp")

# Adding ppack library
add_library(ppack
  STATIC
  "include/ppack.hpp"
  "src/ppack.cpp")


# create the policygen executable
add_executable(policygen "src/policygen.cpp")


# Linking with  boost/program_options library
set(BOOST_VERSION 1.72.0)
find_package(Boost ${BOOST_VERSION} COMPONENTS program_options)
if(Boost_FOUND)
  include_directories(${Boost_INCLUDE_DIRS})
  target_link_libraries(policygen ${Boost_LIBRARIES})
endif()


# link with mask  dependences
target_link_libraries(policygen mask)

# link with ppack  dependences
target_link_libraries(policygen ppack)
