cmake_minimum_required(VERSION 2.8.8)
set(PROJECT_NAME_STR CactusJumpTests)
project(${PROJECT_NAME_STR} C CXX)

find_package(Threads REQUIRED)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(CMAKE_COMPILER_IS_GNUCXX)
  add_compile_options(-Wall -ansi -Wno-deprecated -pthread -std=c++11 -pedantic)
endif()

# set common include folder for module
set(COMMON_INCLUDES 
  ${PROJECT_SOURCE_DIR}/lib/asset
  ${PROJECT_SOURCE_DIR}/lib/obstacle
  ${PROJECT_SOURCE_DIR}/lib/player
  ${PROJECT_SOURCE_DIR}/lib/shared
  )
MESSAGE(STATUS "COMMON_INCLUDES: " ${COMMON_INCLUDES})

set(EXT_PROJECTS_DIR ${PROJECT_SOURCE_DIR}/ext)

# GTest
include(${EXT_PROJECTS_DIR}/gtest/GoogleTest.cmake)
include_directories(${GTEST_INCLUDE_DIRS} ${COMMON_INCLUDES})

# Build shared library and link it to test project
add_subdirectory(lib)

set(TEST_LINK_LIBRARIES
  CactusJump
  ${GTEST_LIB_PATH}
  ${GTEST_MAIN_PATH}
  pthread)

# create a test binary per test source file
enable_testing()

set(TEST_DIR ${PROJECT_SOURCE_DIR}/test)
set(TEST_SRC_FILES
  ${TEST_DIR}/asset.cpp
  ${TEST_DIR}/player.cpp
  ${TEST_DIR}/collision.cpp
  )

foreach(_test_file ${TEST_SRC_FILES})
    get_filename_component(_test_name ${_test_file} NAME_WE)
    add_executable(${_test_name} ${_test_file})
    add_dependencies(${_test_name} gtest_external)
    target_link_libraries(${_test_name} ${GTEST_LIB_PATH} ${GTEST_MAIN_PATH} pthread CactusJump)
    add_test(${_test_name} ${_test_name})
endforeach()
