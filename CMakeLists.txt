cmake_minimum_required(VERSION 2.8.8)
set(PROJECT_NAME_STR CactusJumpTests)
project(${PROJECT_NAME_STR} C CXX)

find_package(Threads REQUIRED)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
configure_file(ext/gtest/GoogleTest.cmake googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" . 
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download)
if (result)
  message(FATAL_ERROR "CMake step for googletest failed: ${result}")
endif()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download)
if (result)
  message(FATAL_ERROR "Build step for googletest failed: ${result}")
endif()

if(CMAKE_COMPILER_IS_GNUCXX)
  add_compile_options(-Wall -ansi -Wno-deprecated -pthread -std=c++11 -pedantic)
elseif(MSVC)
  # add_compile_options(/NODEFAULTLIB:LIBCMTD)
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

add_subdirectory(${CMAKE_BINARY_DIR}/googletest-src
                 ${CMAKE_BINARY_DIR}/googletest-build
                 EXCLUDE_FROM_ALL)

# Build shared library and link it to test project
add_subdirectory(lib)

set(TEST_LINK_LIBRARIES
  CactusJump
  ${CMAKE_THREAD_LIBS_INIT}
  )

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
    add_dependencies(${_test_name} gtest)
    target_include_directories(${_test_name} PRIVATE ${COMMON_INCLUDES})
        target_link_libraries(${_test_name} 
            ${CMAKE_THREAD_LIBS_INIT} 
        )
    target_link_libraries(${_test_name} gtest_main CactusJump)
    add_test(NAME ${_test_name} COMMAND ${_test_name})
endforeach()
