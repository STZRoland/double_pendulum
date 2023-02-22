cmake_minimum_required(VERSION 3.16)
project(MySDL2App)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find the libraries
find_package(SDL2 REQUIRED)
find_package(Boost REQUIRED)

# Add the SDL2 include directory to the include path
include_directories(${SDL2_INCLUDE_DIRS})

# Add the lib directory
add_subdirectory(lib)

# Set up the build
add_executable(MySDL2App main.cpp)
target_link_libraries(MySDL2App ${SDL2_LIBRARIES} Boost::boost pendulum_lib)
