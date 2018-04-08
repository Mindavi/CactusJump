if(CMAKE_COMPILER_IS_GNUCXX)
  add_compile_options(-Wall -ansi -Wno-deprecated -pthread -std=c++11 -pedantic)
endif()

set(CactusJump_Sources
  ${CMAKE_CURRENT_SOURCE_DIR}/asset/asset.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/player/player.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/obstacle/obstacle.cpp
  )

set(LIBRARY_NAME CactusJump)
add_library(${LIBRARY_NAME} SHARED ${CactusJump_Sources})

