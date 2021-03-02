# policygen compiler instrction
cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

project(PPACK LANGUAGES CXX VERSION 1.0)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# adding mask library
add_library(mask
  STATIC
  "include/mask.hpp"
  "src/mask.cpp")

# adding base library
add_library(basepoli
  STATIC
  "include/basepoli.hpp"
  "src/basepoli.cpp")

# adding pstruct library
add_library(pstructs
  STATIC
  "include/pstructs.hpp"
  "src/pstructs.cpp")

# adding password library
add_library(password
  STATIC
  "include/password.hpp"
  "src/password.cpp")

# adding fineprint library
add_library(fineprint
  STATIC
  "include/fineprint.hpp"
  "src/fineprint.cpp")

# adding csv library
add_library(csv
  STATIC
  "include/csv.hpp"
  "src/csv.cpp")

# Adding ppack library
add_library(ppack
  STATIC
  "include/ppack.hpp"
  "src/ppack.cpp")


###########################################################
######### compiling and linking policygen cli cmd #########
###########################################################

# create the policygen executable
add_executable(policygen "src/policygen.cpp")


# Linking with  boost/program_options library
set(BOOST_VERSION 1.72.0)
find_package(Boost COMPONENTS program_options)
if(Boost_FOUND)
  include_directories(${Boost_INCLUDE_DIRS})
  target_link_libraries(policygen ${Boost_LIBRARIES})
endif()


# linking policygen with library  dependences
target_link_libraries(policygen mask password pstructs basepoli fineprint csv ppack)



##########################################################
######### compiling and linking statsgen cli cmd #########
##########################################################


# # create the policygen executable
# add_executable(statsgen "src/statsgen.cpp")


# # Linking with  boost/program_options and boost/algorithm library
# set(BOOST_VERSION 1.72.0)
# find_package(Boost ${BOOST_VERSION} COMPONENTS program_options)
# if(Boost_FOUND)
#   include_directories(${Boost_INCLUDE_DIRS})
#   target_link_libraries(statsgen ${Boost_LIBRARIES})
# endif()


# # linking statsgen with library  dependences
# target_link_libraries(policygen pstructs mask ppack password basepoli)