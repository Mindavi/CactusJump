cmake_minimum_required(VERSION 2.8.8)
set(PROJECT_NAME_STR CactusJumpTests)
project(${PROJECT_NAME_STR} C CXX)

find_package(Threads REQUIRED)

if(CMAKE_COMPILER_IS_GNUCXX)
    add_definitions(-Wall -ansi -Wno-deprecated -pthread -std=c++11 -pedantic)
endif()

# set common include folder for module
set(COMMON_INCLUDES ${PROJECT_SOURCE_DIR}/lib/asset ${PROJECT_SOURCE_DIR}/lib/obstacle ${PROJECT_SOURCE_DIR}/lib/player ${PROJECT_SOURCE_DIR}/lib/shared)
MESSAGE(STATUS "COMMON_INCLUDES: " ${COMMON_INCLUDES})

set(EXT_PROJECTS_DIR ${PROJECT_SOURCE_DIR}/ext)

# GTest
include(${EXT_PROJECTS_DIR}/gtest/GoogleTest.cmake)

include_directories(${GTEST_INCLUDE_DIRS} ${COMMON_INCLUDES})

file(GLOB TEST_SRC_FILES ${PROJECT_SOURCE_DIR}/test/*.cpp)
add_executable(${PROJECT_NAME_STR} ${TEST_SRC_FILES})
add_dependencies(${PROJECT_NAME_STR} gtest_external)

# Build shared library and link it to test project
add_subdirectory(lib)

set(TEST_LINK_LIBRARIES
  CactusJump
  ${GTEST_LIB_PATH}
  ${GTEST_MAIN_PATH}
  pthread)

MESSAGE(STATUS "GTEST MAIN PATH: " ${GTEST_MAIN_PATH})
MESSAGE(STATUS "CMAKE THEAD LIBS INIT: " ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(${PROJECT_NAME_STR} ${GTEST_LIB_PATH} ${GTEST_MAIN_PATH} pthread CactusJump)

