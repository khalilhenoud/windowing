cmake_minimum_required(VERSION 3.22)

project(windowing_package)

if(ENGINE_BUILD)
add_subdirectory(windowing)
else()
add_subdirectory(windowing_test)
endif()