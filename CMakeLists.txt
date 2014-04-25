#Change this if you need to target a specific CMake version
cmake_minimum_required(VERSION 2.6)
project(SFML_Game)

# Enable debug symbols by default
if(CMAKE_BUILD_TYPE STREQUAL "")
  set(CMAKE_BUILD_TYPE Debug)
endif()
# (you can also set it on the command line: -D CMAKE_BUILD_TYPE=Release)

ADD_SUBDIRECTORY(Engine)

IF (NOT DEFINED ENABLE_TEST)
    SET(ENABLE_TEST FALSE)
ELSEIF (ENABLE_TEST)
  ENABLE_TESTING()
  ADD_SUBDIRECTORY(Test)
ENDIF()
SET(CMAKE_CXX_FLAGS "-std=c++11")

