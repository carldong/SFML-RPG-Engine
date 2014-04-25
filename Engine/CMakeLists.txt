#Change this if you need to target a specific CMake version
CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
PROJECT(SFML_Engine)

# Enable debug symbols by default
IF(CMAKE_BUILD_TYPE STREQUAL "")
  SET(CMAKE_BUILD_TYPE Debug)
ENDIF()
# (you can also set it on the command line: -D CMAKE_BUILD_TYPE=Release)

INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}/Include")

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
  ENABLE_TESTING()
  FIND_PACKAGE(Boost COMPONENTS system filesystem unit_test_framework REQUIRED)
  INCLUDE_DIRECTORIES(
    ${Boost_INCLUDE_DIRS}
    )
  ADD_DEFINITIONS(-DBOOST_TEST_DYN_LINK)

  TARGET_LINK_LIBRARIES(${LIBRARY_NAME}
    ${Boost_FILESYSTEM_LIBRARY}
    ${Boost_SYSTEM_LIBRARY}
    ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
    )
  
  ADD_EXECUTABLE(Test_TestSuite Test/Test_TestSuite.cpp)
  TARGET_LINK_LIBRARIES ( Test_TestSuite
    ${LIBRARY_NAME}
    )
  ADD_TEST(Test_TestSuite Test_TestSuite)
  
  ADD_EXECUTABLE(Test_MessageBus Test/Test_MessageBus.cpp)
  TARGET_LINK_LIBRARIES ( Test_MessageBus
    ${LIBRARY_NAME}
    )
  ADD_TEST(Test_Messagebus Test_MessageBus)
  
  ADD_EXECUTABLE(Test_Game Test/Test_Game.cpp)
  TARGET_LINK_LIBRARIES ( Test_Game
    ${LIBRARY_NAME}
    )
  ADD_TEST(Test_Game Test_Game)

  ADD_EXECUTABLE(Test_Game_Fail Test/Test_Game_Fail.cpp)
  TARGET_LINK_LIBRARIES ( Test_Game_Fail
    ${LIBRARY_NAME}
    )
  ADD_TEST(Test_Game_Fail Test_Game_Fail)
ENDIF()


# Detect and add SFML
SET(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
#Find any version 2.X of SFML
#See the FindSFML.cmake file for additional details and instructions
FIND_PACKAGE(SFML 2 REQUIRED system window graphics network audio)
IF(SFML_FOUND)
  INCLUDE_DIRECTORIES(${SFML_INCLUDE_DIR})
  TARGET_LINK_LIBRARIES(${LIBRARY_NAME} ${SFML_LIBRARIES})
ENDIF()
