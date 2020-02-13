# Specify the minimum version for CMake
cmake_minimum_required( VERSION 3.7.2 )

# Project's name
project( tools )

# Set the output folder where your program will be created
set( CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/test/bin )
set( EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR} )
set( LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR} )
set( TARGET_NAME ${PROJECT_NAME}_Test )

# Include Directories.
set( INCLUDE_DIRECTORIES ${PROJECT_SOURCE_DIR}/inc )
set( INCLUDE_DIRECTORIES ${INCLUDE_DIRECTORIES} ${PROJECT_SOURCE_DIR}/test/inc )
include_directories( ${INCLUDE_DIRECTORIES} )

# Source Files.
file( GLOB APP_SRC "./src/*.c" )
file( GLOB TEST_SRC "./test/src/*.c" )

# Add executable to list.
add_executable( ${TARGET_NAME} ${APP_SRC} ${TEST_SRC} ${DEPENDS_SRC})

# Generate coverage on GCC. Updgrade warnings.
# if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
#     target_compile_options( ${TARGET_NAME} PRIVATE -fprofile-arcs -ftest-coverage -Werror -Wall )
#     target_link_options( ${TARGET_NAME} PRIVATE -lgcov -fprofile-arcs)
# # Only upgrade warnings for MSVC.
# elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
#     set_property( DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${TARGET_NAME} )
#     target_compile_options( ${TARGET_NAME} PRIVATE /W4 /WX )