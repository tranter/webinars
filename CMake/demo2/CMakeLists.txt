cmake_minimum_required(VERSION 3.0)
project(Demo2)

add_executable(Demo2
    demo2.cpp
    hello.cpp
)

# The version number.
set(Demo2_VERSION_MAJOR 1)
set(Demo2_VERSION_MINOR 0)
 
# Configure a header file to pass some of the CMake settings to the
# source code
configure_file(
  "${PROJECT_SOURCE_DIR}/config.h.in"
  "${PROJECT_BINARY_DIR}/config.h"
  )
 
# Add the binary tree to the search path for include files
# so that we will find config.h
include_directories("${PROJECT_BINARY_DIR}")

# Add library to include path
include_directories("${PROJECT_SOURCE_DIR}/mathlib")
add_subdirectory(mathlib)

# Link with math library
target_link_libraries(Demo2 mathlib)

# Add the install targets
install(TARGETS Demo2 DESTINATION bin)
install(FILES "${PROJECT_BINARY_DIR}/config.h" DESTINATION include)
