set(CactusJump_Sources ${CMAKE_CURRENT_SOURCE_DIR}/asset/asset.h ${CMAKE_CURRENT_SOURCE_DIR}/asset/asset.cpp)

add_library(CactusJump SHARED ${CactusJump_Sources})
MESSAGE(STATUS "COMMON_INCLUDES: " ${COMMON_INCLUDES})
target_link_libraries(CactusJump ${CactusJump_Sources})

# set_target_properties(CactusJump PROPERTIES LINKER_LANGUAGE CXX)