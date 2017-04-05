# cmake needs this line
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
cmake_minimum_required(VERSION 3.2.2.)

# Define project name
project(opencv_gtkmm3_barebone)
set(CMAKE_CXX_STANDARD 14)
set(THREADS_PREFER_PTHREAD_FLAG ON)

find_package(Threads REQUIRED)
find_package(OpenCV REQUIRED)
find_package(gtkmm REQUIRED)

aux_source_directory(src/ SRC_LIST)

add_executable(${PROJECT_NAME} ${SRC_LIST})
target_link_libraries(${PROJECT_NAME} Threads::Threads ${OpenCV_LIBS})
