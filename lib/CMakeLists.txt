# Define the library target
add_library(pendulum_lib Pendulum.cpp Pendulum.h Rendering.cpp Rendering.h)

# Set the include directories for the library target
target_include_directories(pendulum_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})