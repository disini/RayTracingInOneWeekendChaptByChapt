cmake_minimum_required(VERSION 3.1.0)

project(Code03
        VERSION 3.0.0
        LANGUAGES CXX
)

# Set to c++ 11
set(CMAKE_CXX_STANDARD 11)

# 交叉编译
#set(CMAKE_CROSSCOMPILING 1)
#set(CROSS_COMPILE 1)

#if (CROSS_COMPILE)
#    set(CMAKE_SYSTEM_NAME "Linux")
#endif ()

message(STATUS "CMAKE_SYSTEM_NAME : ${CMAKE_SYSTEM_NAME}")

if (CMAKE_SYSTEM_NAME STREQUAL "Linux")
    set(PROJECT_BINARY_DIR "${CMAKE_CURRENT_SOURCE_DIR}/build_ubuntu_clion")
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_CURRENT_SOURCE_DIR}/build_ubuntu_clion/Debug")
    set(EXECUTABLE_OUTPUT_PATH_DEBUG "${CMAKE_CURRENT_SOURCE_DIR}/build_ubuntu_clion/Debug")
    set(LIBRARY_OUTPUT_PATH_DEBUG "${CMAKE_CURRENT_SOURCE_DIR}/build_ubuntu_clion/Debug")
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_CURRENT_SOURCE_DIR}/build_ubuntu_clion/Release")
    set(EXECUTABLE_OUTPUT_PATH_RELEASE "${CMAKE_CURRENT_SOURCE_DIR}/build_ubuntu_clion/Release")
    set(LIBRARY_OUTPUT_PATH_RELEASE "${CMAKE_CURRENT_SOURCE_DIR}/build_ubuntu_clion/Release")
    #set(EXECUTABLE_OUTPUT_PATH "${CMAKE_CURRENT_SOURCE_DIR}/build_ubuntu_clion")
elseif(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    set(PROJECT_BINARY_DIR "${CMAKE_CURRENT_SOURCE_DIR}/build_windows_clion")
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_CURRENT_SOURCE_DIR}/build_windows_clion/Debug")
    set(EXECUTABLE_OUTPUT_PATH_DEBUG "${CMAKE_CURRENT_SOURCE_DIR}/build_windows_clion/Debug")
    set(LIBRARY_OUTPUT_PATH_DEBUG "${CMAKE_CURRENT_SOURCE_DIR}/build_windows_clion/Debug")
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_CURRENT_SOURCE_DIR}/build_windows_clion/Release")
    set(EXECUTABLE_OUTPUT_PATH_RELEASE "${CMAKE_CURRENT_SOURCE_DIR}/build_windows_clion/Release")
    set(LIBRARY_OUTPUT_PATH_RELEASE "${CMAKE_CURRENT_SOURCE_DIR}/build_windows_clion/Release")
    #set(EXECUTABLE_OUTPUT_PATH "${CMAKE_CURRENT_SOURCE_DIR}/build_windows_clion")
else ( message(STATUS "Cur System : ${CMAKE_SYSTEM_NAME}"))
endif ()


# Source



set(    SOURCE_BOOK_3_PROJ_02
        02_A_Simple_Monte_Carlo_Program/src/pi.cpp)

set(    SOURCE_BOOK_3_PROJ_03

        03_One_Dimensional_MC_Integration/src/integrate_x_sq.cpp
)

set(SOURCE_BOOK_3_PROJ_04
        04_MC_Integration_on_the_Sphere_of_Directions/src/sphere_importance.cpp
)

set(SOURCE_BOOK_3_PROJ_06
        06_Importance_Sampling_Materials/src/main.cpp
)

set(SOURCE_BOOK_3_PROJ_07
        07_Generating_Random_Directions/src/cos_density.cc
)

set(SOURCE_BOOK_3_PROJ_08
        08_Orthonormal_Bases/src/main.cpp
)

set(SOURCE_BOOK_3_PROJ_09
        09_Sampling_Lights_Directly/src/main.cpp
)

set(SOURCE_BOOK_3_PROJ_10
        10_Mixture_Densities/src/main.cpp
)




# Executables

add_executable(02_A_Simple_Monte_Carlo_Program ${SOURCE_BOOK_3_PROJ_02})
add_executable(03_One_Dimensional_MC_Integration ${SOURCE_BOOK_3_PROJ_03})
add_executable(04_MC_Integration_on_the_Sphere_of_Directions ${SOURCE_BOOK_3_PROJ_04})
add_executable(06_Importance_Sampling_Materials ${SOURCE_BOOK_3_PROJ_06})
add_executable(07_Generating_Random_Directions ${SOURCE_BOOK_3_PROJ_07})
add_executable(08_Orthonormal_Bases ${SOURCE_BOOK_3_PROJ_08})
add_executable(09_Sampling_Lights_Directly ${SOURCE_BOOK_3_PROJ_09})
add_executable(10_Mixture_Densities ${SOURCE_BOOK_3_PROJ_10})

message(STATUS "PROJECT_BINARY_DIR: ${PROJECT_BINARY_DIR}")
message(STATUS "PROJECT_SOURCE_DIR: ${PROJECT_SOURCE_DIR}")
