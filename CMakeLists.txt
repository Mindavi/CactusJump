cmake_minimum_required(VERSION 2.8.8)
set(PROJECT_NAME_STR CactusJumpTests)
project(${PROJECT_NAME_STR} C CXX)

find_package(Threads REQUIRED)

if(CMAKE_COMPILER_IS_GNUCXX)
    add_definitions(-Wall -ansi -Wno-deprecated -std=c++11 -pedantic)
endif()

if(MSVC)
    #vc 2012 fix for vararg templates
    set(MSVC_COMPILER_DEFS "-D_VARIADIC_MAX=10")
endif() 

# set common include folder for module
set(COMMON_INCLUDES ${PROJECT_SOURCE_DIR}/lib/asset ${PROJECT_SOURCE_DIR}/lib/obstacle ${PROJECT_SOURCE_DIR}/lib/player ${PROJECT_SOURCE_DIR}/lib/shared)
MESSAGE(STATUS "COMMON_INCLUDES: " ${COMMON_INCLUDES})

set(EXT_PROJECTS_DIR ${PROJECT_SOURCE_DIR}/ext)

set(TEST_LINK_LIBRARIES
  CactusJump
  ${GTEST_LIB_PATH}
  ${GTEST_MAIN_PATH}
  ${CMAKE_THREAD_LIBS_INIT})

add_subdirectory(${EXT_PROJECTS_DIR}/gtest)
include_directories(${GTEST_INCLUDE_DIRS} ${COMMON_INCLUDES})

# GTest
add_definitions(${MSVC_COMPILER_DEFS})
enable_testing()

# Build library
add_subdirectory(lib)

# create a test binary per test source file
set(TEST_SRC_FILES
  ${PROJECT_SOURCE_DIR}/test/asset.cpp
  ${PROJECT_SOURCE_DIR}/test/player.cpp)

foreach(_test_file ${TEST_SRC_FILES})
    get_filename_component(_test_name ${_test_file} NAME_WE)
    add_executable(${_test_name} ${_test_file})
    add_dependencies(${_test_name} googletest)
    target_link_libraries(${_test_name} ${TEST_LINK_LIBRARIES})
    if(NOT WIN32 OR MINGW)
      target_link_libraries(${_test_name}
        ${GTEST_LIBS_DIR}/libgtest.a
        ${GTEST_LIBS_DIR}/libgtest_main.a)
    else()
      target_link_libraries(${_test_name}
        debug ${GTEST_LIBS_DIR}/DebugLibs/${CMAKE_FIND_LIBRARY_PREFIXES}gtestd${CMAKE_FIND_LIBRARY_SUFFIXES}
        optimized ${GTEST_LIBS_DIR}/ReleaseLibs/${CMAKE_FIND_LIBRARY_PREFIXES}gtest${CMAKE_FIND_LIBRARY_SUFFIXES})
      target_link_libraries(${_test_name}
        debug ${GTEST_LIBS_DIR}/DebugLibs/${CMAKE_FIND_LIBRARY_PREFIXES}gtest_maind${CMAKE_FIND_LIBRARY_SUFFIXES}
        optimized ${GTEST_LIBS_DIR}/ReleaseLibs/${CMAKE_FIND_LIBRARY_PREFIXES}gtest_main${CMAKE_FIND_LIBRARY_SUFFIXES})
    endif()
    add_test(${_test_name} ${_test_name})
endforeach()
