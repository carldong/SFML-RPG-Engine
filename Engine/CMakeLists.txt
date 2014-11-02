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
  "${CMAKE_CURRENT_SOURCE_DIR}/Include/MessageBus.hpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/Source/MessageBus/*.cpp"
  )
FILE(GLOB RENDERER_SRC
  "${CMAKE_CURRENT_SOURCE_DIR}/Include/Renderer/*.hpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/Include/Resources/*.hpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/Source/Renderer/*.cpp"
  )
FILE(GLOB DNA_SRC
  "${CMAKE_CURRENT_SOURCE_DIR}/Include/DNA/*.hpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/Source/DNA/*.cpp"
  )
# Define sources and executable
SET(EXECUTABLE_NAME "game")
SET(MAIN_LIBRARY "DEngine")
SET(MESSAGEBUS_LIB "DMessageBus")
SET(RENDERER_LIB "DRenderer")
SET(DNA_LIB "DDNA")

ADD_LIBRARY(${MESSAGEBUS_LIB} SHARED ${MESSAGEBUS_SRC})
ADD_LIBRARY(${MAIN_LIBRARY} SHARED ${GAME_SRC})
ADD_LIBRARY(${RENDERER_LIB} SHARED ${RENDERER_SRC})
ADD_LIBRARY(${DNA_LIB} SHARED ${DNA_SRC})
ADD_EXECUTABLE(${EXECUTABLE_NAME} Main.cpp)

TARGET_LINK_LIBRARIES(${RENDERER_LIB}
  ${MESSAGEBUS_LIB}
  )
TARGET_LINK_LIBRARIES(${MAIN_LIBRARY}
  ${MESSAGEBUS_LIB}
  ${RENDERER_LIB}
  ${DNA_LIB}
  )
TARGET_LINK_LIBRARIES(${EXECUTABLE_NAME} ${MAIN_LIBRARY})

IF (ENABLE_TEST)
  CONFIGURE_FILE(Test/assets/test_texture.png Test/assets/test_texture.png COPYONLY)
  ENABLE_TESTING()
  FIND_PACKAGE(Boost COMPONENTS system filesystem unit_test_framework REQUIRED)
  INCLUDE_DIRECTORIES(
    ${Boost_INCLUDE_DIRS}
    )
  ADD_DEFINITIONS(-DBOOST_TEST_DYN_LINK)

  TARGET_LINK_LIBRARIES(${MAIN_LIBRARY}
    ${Boost_FILESYSTEM_LIBRARY}
    ${Boost_SYSTEM_LIBRARY}
    ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
    )

  # Make sure test suite works
  ADD_EXECUTABLE(Test/Test_TestSuite Test/Test_TestSuite.cpp)
  TARGET_LINK_LIBRARIES ( Test/Test_TestSuite
    ${MAIN_LIBRARY}
    )
  ADD_TEST(Test_TestSuite Test/Test_TestSuite)
  
  ADD_EXECUTABLE(Test/Test_MessageBus Test/Test_MessageBus.cpp)
  TARGET_LINK_LIBRARIES ( Test/Test_MessageBus
    ${MAIN_LIBRARY}
    )
  ADD_TEST(Test_Messagebus Test/Test_MessageBus)
  
  # Game and Messagebus
  ADD_EXECUTABLE(Test/Test_Game Test/Test_Game.cpp)
  TARGET_LINK_LIBRARIES ( Test/Test_Game
    ${MAIN_LIBRARY}
    )
  ADD_TEST(Test_Game Test/Test_Game)  

  ADD_EXECUTABLE(Test/Test_SceneNode Test/Test_SceneNode.cpp)
  TARGET_LINK_LIBRARIES(Test/Test_SceneNode
    ${MAIN_LIBRARY}
    )
  ADD_TEST(Test_SceneNode Test/Test_SceneNode)

  # With X
  ADD_EXECUTABLE(Test/Test_SFMLNode Test/Test_SFMLNode.cpp)
  TARGET_LINK_LIBRARIES(Test/Test_SFMLNode
    ${MAIN_LIBRARY}
    )
  ADD_TEST(Test_SFMLNode Test/Test_SFMLNode)

  # With X
  ADD_EXECUTABLE(Test/Test_Resources Test/Test_Resources.cpp)
  TARGET_LINK_LIBRARIES(Test/Test_Resources
    ${MAIN_LIBRARY}
    )
  ADD_TEST(Test_Resources Test/Test_Resources)
  
  # With X
  ADD_EXECUTABLE(Test/Test_Scene Test/Test_Scene.cpp)
  TARGET_LINK_LIBRARIES(Test/Test_Scene
    ${MAIN_LIBRARY}
    )
  ADD_TEST(Test_Scene Test/Test_Scene)

  # With X
  ADD_EXECUTABLE(Test/Test_Renderer Test/Test_Renderer.cpp)
  TARGET_LINK_LIBRARIES(Test/Test_Renderer
    ${MAIN_LIBRARY}
    )
  ADD_TEST(Test_Renderer Test/Test_Renderer)

ENDIF()


# Detect and add SFML
SET(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
#Find any version 2.X of SFML
#See the FindSFML.cmake file for additional details and instructions
FIND_PACKAGE(SFML 2 REQUIRED system window graphics network audio)
IF(SFML_FOUND)
  INCLUDE_DIRECTORIES(${SFML_INCLUDE_DIR})
  TARGET_LINK_LIBRARIES(${MAIN_LIBRARY} ${SFML_LIBRARIES})
ENDIF()
