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

# set(DEBUG 1) #this compilation support unittest test
# if(DEBUG)
#   find_package(UnitTest++)
# endif()



## compiling and linking policygen cli cmd

# create the policygen executable
add_executable(policygen "src/policygen.cpp")


# Linking with  boost/program_options library
set(BOOST_VERSION 1.72.0)
find_package(Boost ${BOOST_VERSION} COMPONENTS program_options)
if(Boost_FOUND)
  include_directories(${Boost_INCLUDE_DIRS})
  target_link_libraries(policygen ${Boost_LIBRARIES})
endif()


# linking policygen with mask  dependences
target_link_libraries(policygen mask)

# linking policygen with ppack  dependences
target_link_libraries(policygen ppack)



## compiling and linking statsgen cli cmd


# create the policygen executable
add_executable(statsgen "src/statsgen.cpp")


# Linking with  boost/program_options and boost/algorithm library
set(BOOST_VERSION 1.72.0)
find_package(Boost ${BOOST_VERSION} COMPONENTS program_options algorithm)
if(Boost_FOUND)
  include_directories(${Boost_INCLUDE_DIRS})
  target_link_libraries(statsgen ${Boost_LIBRARIES})
endif()


# linking statsgen with mask  dependences
target_link_libraries(policygen mask)

# linking statsgen with ppack  dependences
target_link_libraries(policygen ppack)
