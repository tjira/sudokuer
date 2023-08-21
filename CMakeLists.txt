cmake_minimum_required(VERSION 3.16)
set(CMAKE_CXX_STANDARD 20)
project(Sudokuer)

# set output flags
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# set compiler flags
set(CMAKE_CXX_FLAGS_DEBUG "-g -pg -O0 -fprofile-arcs -ftest-coverage -Wall -Wextra")
set(CMAKE_CXX_FLAGS_RELEASE "-s -O3")

# set the variable that contains the compile flags
if(${CMAKE_BUILD_TYPE} STREQUAL Debug)
    set(CXXFLAGS ${CMAKE_CXX_FLAGS_DEBUG})
elseif(${CMAKE_BUILD_TYPE} STREQUAL Release)
    set(CXXFLAGS ${CMAKE_CXX_FLAGS_RELEASE})
endif()

# include necessary directories
include_directories(include lib)

# find the necessary packages
find_package(OpenMP)

# add fractoid executable
add_executable(sudokuer src/main.cpp src/sudoku.cpp)

# link OpenMP on build type
if(OPENMP_FOUND AND ${CMAKE_BUILD_TYPE} STREQUAL Release)
    target_link_libraries(sudokuer OpenMP::OpenMP_CXX)
endif()
