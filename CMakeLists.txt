# cmake needs this line
cmake_minimum_required(VERSION 3.2.2.)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
set(CMAKE_CXX_STANDARD 14)
set(THREADS_PREFER_PTHREAD_FLAG ON)

include(FindPkgConfig)
# ==================================================================

# Define project name
project(opencv_gtkmm3_barebone)

# Add opencv dependence
find_package(Threads REQUIRED)
find_package(OpenCV REQUIRED)

# For gtkmm3
pkg_check_modules(PKG REQUIRED gtkmm-3.0)
include_directories(${PKG_INCLUDE_DIRS})
link_libraries(${PKG_LIBRARIES})
link_directories(${PKG_LIBRARY_DIRS})

# ------------------------------------------------------------------
aux_source_directory(src/ SRC_LIST)

add_executable(${PROJECT_NAME} ${SRC_LIST})
target_link_libraries(${PROJECT_NAME} Threads::Threads ${OpenCV_LIBS})

# ------------------------------------------------------------------
message(STATUS "Configuration status:")
message(STATUS "    opencv: version: ${OpenCV_VERSION}")
message(STATUS "            libraries: ${OpenCV_LIBS}")
message(STATUS "            include path: ${OpenCV_INCLUDE_DIRS}")