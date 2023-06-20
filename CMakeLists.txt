# CMakeLists.txt has to be located in the project folder and cmake has to be
# executed from 'project/build' with 'cmake ../'.
cmake_minimum_required(VERSION 3.9)
project(water_probe_acquanativa_ap3
        VERSION 0.1
        DESCRIPTION "Driver for the Acquanativa Acqua Probe AP3 sensor")
find_package(Rock)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

rock_init()
rock_standard_layout()
