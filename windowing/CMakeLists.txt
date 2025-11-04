cmake_minimum_required(VERSION 3.22)

# set the project name
project(windowing VERSION 1.0)

# specify the cpp standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# add the executable
add_library(${PROJECT_NAME} SHARED ./source/windowing.c)
			
target_link_libraries(${PROJECT_NAME} PRIVATE winmm)

target_include_directories(${PROJECT_NAME} PUBLIC 
							"${PROJECT_SOURCE_DIR}/include")