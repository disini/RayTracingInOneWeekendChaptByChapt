cmake_minimum_required( VERSION 3.1.0 )

project( Code01
        VERSION 3.0.0
        LANGUAGES CXX
)

# Set to c++11
set(CMAKE_CXX_STANDARD 11)

message(STATUS "CMAKE_SYSTEM_NAME : ${CMAKE_SYSTEM_NAME}")

#[[
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
]]





# Source
set(    SOURCE_BOOK_1_PROJ_01
        01_Output_PPM/src/main.cpp
)

set(    SOURCE_BOOK_1_PROJ_02
        02_Add_Rays/src/color.h
        02_Add_Rays/src/ray.h
        02_Add_Rays/src/vec3.h
        02_Add_Rays/src/main.cpp
)

set( SOURCE_BOOK_1_PROJ_03
        03_Add_Sphere/src/color.h
        03_Add_Sphere/src/ray.h
        03_Add_Sphere/src/vec3.h
        03_Add_Sphere/src/camera.h
        03_Add_Sphere/src/hittable.h
        03_Add_Sphere/src/hittable_list.h
        03_Add_Sphere/src/sphere.h
        03_Add_Sphere/src/rtweekend.h
        03_Add_Sphere/src/main.cpp
)

set( SOURCE_BOOK_1_PROJ_04
        04_Diffuse_Materials/src/color.h
        04_Diffuse_Materials/src/ray.h
        04_Diffuse_Materials/src/vec3.h
        04_Diffuse_Materials/src/camera.h
        04_Diffuse_Materials/src/hittable.h
        04_Diffuse_Materials/src/hittable_list.h
        04_Diffuse_Materials/src/sphere.h
        04_Diffuse_Materials/src/rtweekend.h
        04_Diffuse_Materials/src/main.cpp
)

set( SOURCE_BOOK_1_PROJ_05
        05_Metal/src/color.h
        05_Metal/src/ray.h
        05_Metal/src/vec3.h
        05_Metal/src/camera.h
        05_Metal/src/hittable.h
        05_Metal/src/hittable_list.h
        05_Metal/src/sphere.h
        05_Metal/src/rtweekend.h
        05_Metal/src/material.h
        05_Metal/src/main.cpp
        )

set( SOURCE_BOOK_1_PROJ_06
        06_Dielectrics-Glass/src/color.h
        06_Dielectrics-Glass/src/ray.h
        06_Dielectrics-Glass/src/vec3.h
        06_Dielectrics-Glass/src/camera.h
        06_Dielectrics-Glass/src/hittable.h
        06_Dielectrics-Glass/src/hittable_list.h
        06_Dielectrics-Glass/src/sphere.h
        06_Dielectrics-Glass/src/rtweekend.h
        06_Dielectrics-Glass/src/material.h
        06_Dielectrics-Glass/src/main.cpp
        )

set(    SOURCE_BOOK_1_PROJ_07
        07_Camera/src/camera.h
        07_Camera/src/color.h
        07_Camera/src/hittable.h
        07_Camera/src/hittable_list.h
        07_Camera/src/material.h
        07_Camera/src/ray.h
        07_Camera/src/rtweekend.h
        07_Camera/src/sphere.h
        07_Camera/src/vec3.h
        07_Camera/src/main.cpp
)

set(    SOURCE_BOOK_1_PROJ_08
        08_Final_Render/src/camera.h
        08_Final_Render/src/color.h
        08_Final_Render/src/hittable.h
        08_Final_Render/src/hittable_list.h
        08_Final_Render/src/material.h
        08_Final_Render/src/ray.h
        08_Final_Render/src/rtweekend.h
        08_Final_Render/src/sphere.h
        08_Final_Render/src/vec3.h
        08_Final_Render/src/main.cpp
)

# Executables
add_executable(01_Output_PPM ${SOURCE_BOOK_1_PROJ_01})
add_executable(02_Add_Rays ${SOURCE_BOOK_1_PROJ_02})
add_executable(03_Add_Sphere ${SOURCE_BOOK_1_PROJ_03})
add_executable(04_Diffuse_Materials ${SOURCE_BOOK_1_PROJ_04})
add_executable(05_Metal ${SOURCE_BOOK_1_PROJ_05})
add_executable(06_Dielectrics-Glass ${SOURCE_BOOK_1_PROJ_06})
add_executable(07_Camera ${SOURCE_BOOK_1_PROJ_07})
add_executable(08_Final_Render ${SOURCE_BOOK_1_PROJ_08})


message(STATUS "PROJECT_BINARY_DIR: ${PROJECT_BINARY_DIR}")
message(STATUS "PROJECT_SOURCE_DIR: ${PROJECT_SOURCE_DIR}")