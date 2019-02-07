# Build a library of math functions
project(mathlib)
add_library(mathlib SHARED mysqrt.cpp)

# Install targets
install(TARGETS mathlib DESTINATION lib)
install(FILES mysqrt.h DESTINATION include)
