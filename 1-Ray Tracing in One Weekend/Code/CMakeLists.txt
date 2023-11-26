cmake_minimum_required( VERSION 3.1.0 )

project( Code01
        VERSION 3.0.0
        LANGUAGES CXX
)

# Set to c++ 20
set(CMAKE_CXX_STANDARD 20)

# 交叉编译
#set(CMAKE_CROSSCOMPILING 1)
#set(CROSS_COMPILE 1)
#
#if (CROSS_COMPILE)
##    set(CMAKE_SYSTEM_NAME "Linux")
#    set(CMAKE_SYSTEM_NAME "Windows")
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
set(    SOURCE_BOOK_1_PROJ_02
        02_Output_PPM/src/main.cpp
)

set(    SOURCE_BOOK_1_PROJ_04
        04_Add_Rays/src/color.h
        04_Add_Rays/src/ray.h
        04_Add_Rays/src/vec3.h
        04_Add_Rays/src/main.cpp
)

set( SOURCE_BOOK_1_PROJ_05
        05_Adding_a_Sphere/src/color.h
        05_Adding_a_Sphere/src/ray.h
        05_Adding_a_Sphere/src/vec3.h
        05_Adding_a_Sphere/src/main.cpp
)

set( SOURCE_BOOK_1_PROJ_06
        06_Surface_Normals_and_Multiple_Objects/src/color.h
        06_Surface_Normals_and_Multiple_Objects/src/ray.h
        06_Surface_Normals_and_Multiple_Objects/src/vec3.h
#        06_Surface_Normals_and_Multiple_Objects/src/camera.h
        06_Surface_Normals_and_Multiple_Objects/src/hittable.h
        06_Surface_Normals_and_Multiple_Objects/src/hittable_list.h
        06_Surface_Normals_and_Multiple_Objects/src/sphere.h
        06_Surface_Normals_and_Multiple_Objects/src/rtweekend.h
        06_Surface_Normals_and_Multiple_Objects/src/main.cpp
)

set( SOURCE_BOOK_1_PROJ_07
        07_Antialiasing/src/color.h
        07_Antialiasing/src/ray.h
        07_Antialiasing/src/vec3.h
        07_Antialiasing/src/camera.h
        07_Antialiasing/src/hittable.h
        07_Antialiasing/src/hittable_list.h
        07_Antialiasing/src/sphere.h
        07_Antialiasing/src/rtweekend.h
        07_Antialiasing/src/main.cpp
)

set( SOURCE_BOOK_1_PROJ_08
        08_Diffuse_Materials/src/color.h
        08_Diffuse_Materials/src/ray.h
        08_Diffuse_Materials/src/vec3.h
        08_Diffuse_Materials/src/camera.h
        08_Diffuse_Materials/src/hittable.h
        08_Diffuse_Materials/src/hittable_list.h
        08_Diffuse_Materials/src/sphere.h
        08_Diffuse_Materials/src/rtweekend.h
        08_Diffuse_Materials/src/main.cpp
)

set( SOURCE_BOOK_1_PROJ_09
        09_Metal/src/color.h
        09_Metal/src/ray.h
        09_Metal/src/vec3.h
        09_Metal/src/camera.h
        09_Metal/src/hittable.h
        09_Metal/src/hittable_list.h
        09_Metal/src/sphere.h
        09_Metal/src/rtweekend.h
        09_Metal/src/material.h
        09_Metal/src/main.cpp
)

set( SOURCE_BOOK_1_PROJ_10
        10_Dielectrics-Glass/src/color.h
        10_Dielectrics-Glass/src/ray.h
        10_Dielectrics-Glass/src/vec3.h
        10_Dielectrics-Glass/src/camera.h
        10_Dielectrics-Glass/src/hittable.h
        10_Dielectrics-Glass/src/hittable_list.h
        10_Dielectrics-Glass/src/sphere.h
        10_Dielectrics-Glass/src/rtweekend.h
        10_Dielectrics-Glass/src/material.h
        10_Dielectrics-Glass/src/main.cpp
)

set( SOURCE_BOOK_1_PROJ_11
        11_Positionable_Camera/src/camera.h
        11_Positionable_Camera/src/color.h
        11_Positionable_Camera/src/hittable.h
        11_Positionable_Camera/src/hittable_list.h
        11_Positionable_Camera/src/material.h
        11_Positionable_Camera/src/ray.h
        11_Positionable_Camera/src/rtweekend.h
        11_Positionable_Camera/src/sphere.h
        11_Positionable_Camera/src/vec3.h
        11_Positionable_Camera/src/main.cpp
)

set( SOURCE_BOOK_1_PROJ_12
        12_Defocus_Blur/src/camera.h
        12_Defocus_Blur/src/color.h
        12_Defocus_Blur/src/hittable.h
        12_Defocus_Blur/src/hittable_list.h
        12_Defocus_Blur/src/material.h
        12_Defocus_Blur/src/ray.h
        12_Defocus_Blur/src/rtweekend.h
        12_Defocus_Blur/src/sphere.h
        12_Defocus_Blur/src/vec3.h
        12_Defocus_Blur/src/main.cpp
)

set( SOURCE_BOOK_1_PROJ_13
        13_Final_Render/src/camera.h
        13_Final_Render/src/color.h
        13_Final_Render/src/hittable.h
        13_Final_Render/src/hittable_list.h
        13_Final_Render/src/material.h
        13_Final_Render/src/ray.h
        13_Final_Render/src/rtweekend.h
        13_Final_Render/src/sphere.h
        13_Final_Render/src/vec3.h
        13_Final_Render/src/main.cpp
)

# Executables
add_executable(02_Output_PPM ${SOURCE_BOOK_1_PROJ_02})
add_executable(04_Add_Rays ${SOURCE_BOOK_1_PROJ_04})
add_executable(05_Adding_a_Sphere ${SOURCE_BOOK_1_PROJ_05})
add_executable(06_Surface_Normals_and_Multiple_Objects ${SOURCE_BOOK_1_PROJ_06})
add_executable(07_Antialiasing ${SOURCE_BOOK_1_PROJ_07})
add_executable(08_Diffuse_Materials ${SOURCE_BOOK_1_PROJ_08})
add_executable(09_Metal ${SOURCE_BOOK_1_PROJ_09})
add_executable(10_Dielectrics-Glass ${SOURCE_BOOK_1_PROJ_10})
add_executable(11_Positionable_Camera ${SOURCE_BOOK_1_PROJ_11})
add_executable(12_Defocus_Blur ${SOURCE_BOOK_1_PROJ_12})
add_executable(13_Final_Render ${SOURCE_BOOK_1_PROJ_13})


message(STATUS "PROJECT_BINARY_DIR: ${PROJECT_BINARY_DIR}")
message(STATUS "PROJECT_SOURCE_DIR: ${PROJECT_SOURCE_DIR}")