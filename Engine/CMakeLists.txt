#Change this if you need to target a specific CMake version
cmake_minimum_required(VERSION 2.6)
project(SFML_Engine)

# Enable debug symbols by default
if(CMAKE_BUILD_TYPE STREQUAL "")
  set(CMAKE_BUILD_TYPE Debug)
endif()
# (you can also set it on the command line: -D CMAKE_BUILD_TYPE=Release)

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/Include")

SET(CMAKE_CXX_FLAGS "-std=c++11")


FILE(GLOB GAME_SRC 
    "${CMAKE_CURRENT_SOURCE_DIR}/Include/*.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Source/*.cpp"
    )

# Define sources and executable
SET(EXECUTABLE_NAME "game")
SET(LIBRARY_NAME "DEngine")
ADD_LIBRARY(${LIBRARY_NAME} ${GAME_SRC})
ADD_EXECUTABLE(${EXECUTABLE_NAME} Main.cpp)
TARGET_LINK_LIBRARIES(${EXECUTABLE_NAME} ${LIBRARY_NAME})

IF (ENABLE_TEST)
  FIND_PACKAGE(Boost COMPONENTS system filesystem unit_test_framework REQUIRED)
  INCLUDE_DIRECTORIES(
    ${Boost_INCLUDE_DIRS}
    )
  ADD_DEFINITIONS(-DBOOST_TEST_DYN_LINK)
  
  ADD_EXECUTABLE(Test_MessageBus Test/Test_MessageBus.cpp)
  TARGET_LINK_LIBRARIES ( Test_MessageBus
    ${LIBRARY_NAME}
    ${Boost_FILESYSTEM_LIBRARY}
    ${Boost_SYSTEM_LIBRARY}
    ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
    )
  ENABLE_TESTING()
ENDIF()


# Detect and add SFML
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
#Find any version 2.X of SFML
#See the FindSFML.cmake file for additional details and instructions
find_package(SFML 2 REQUIRED system window graphics network audio)
if(SFML_FOUND)
  include_directories(${SFML_INCLUDE_DIR})
  target_link_libraries(${EXECUTABLE_NAME} ${SFML_LIBRARIES})
endif()
