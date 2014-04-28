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
   "${CMAKE_CURRENT_SOURCE_DIR}/Source/*.cpp"
   )

 FILE(GLOB MESSAGEBUS_SRC
   "${CMAKE_CURRENT_SOURCE_DIR}/Source/MessageBus/*.cpp"
   )
 FILE(GLOB RENDERER_SRC
   "${CMAKE_CURRENT_SOURCE_DIR}/Source/Renderer/*.cpp"
   )
# Define sources and executable
SET(EXECUTABLE_NAME "game")
SET(LIBRARY_NAME "DEngine")
SET(MESSAGEBUS_LIB "DMessageBus")
SET(RENDERER_LIB "DRenderer")

ADD_LIBRARY(${MESSAGEBUS_LIB} SHARED ${MESSAGEBUS_SRC})
ADD_LIBRARY(${LIBRARY_NAME} SHARED ${GAME_SRC})
ADD_LIBRARY(${RENDERER_LIB} SHARED ${RENDERER_SRC})
ADD_EXECUTABLE(${EXECUTABLE_NAME} Main.cpp)

TARGET_LINK_LIBRARIES(${LIBRARY_NAME}
  ${MESSAGEBUS_LIB}
  ${RENDERER_LIB}
  )
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

  # Make sure test suite works
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

  ADD_EXECUTABLE(Test_SceneNode Test/Test_SceneNode.cpp)
  TARGET_LINK_LIBRARIES(Test_SceneNode
    ${LIBRARY_NAME}
    )
  ADD_TEST(Test_SceneNode Test_SceneNode)

  # With X
  ADD_EXECUTABLE(Test_SFMLNode Test/Test_SFMLNode.cpp)
  TARGET_LINK_LIBRARIES(Test_SFMLNode
    ${LIBRARY_NAME}
    )
  ADD_TEST(Test_SFMLNode Test_SFMLNode)

  # With X
  ADD_EXECUTABLE(Test_Scene Test/Test_Scene.cpp)
  TARGET_LINK_LIBRARIES(Test_Scene
    ${LIBRARY_NAME}
    )
  ADD_TEST(Test_Scene Test_Scene)
  
  # Game and Messagebus
  ADD_EXECUTABLE(Test_Game Test/Test_Game.cpp)
  TARGET_LINK_LIBRARIES ( Test_Game
    ${LIBRARY_NAME}
    )
  ADD_TEST(Test_Game Test_Game)
  
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
