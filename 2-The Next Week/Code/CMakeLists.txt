cmake_minimum_required( VERSION 3.1.0 )

project( Code02
        VERSION 3.0.0
        LANGUAGES CXX
)

# Set to c++11
set(CMAKE_CXX_STANDARD 11)

# Ωª≤Ê±‡“Î
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



set(    SOURCE_BOOK_2_PROJ_02
        02_Motion_Blur/src/camera.h
        02_Motion_Blur/src/color.h
        02_Motion_Blur/src/hittable.h
        02_Motion_Blur/src/hittable_list.h
        02_Motion_Blur/src/material.h
        02_Motion_Blur/src/ray.h
        02_Motion_Blur/src/rtweekend.h
        02_Motion_Blur/src/sphere.h
        02_Motion_Blur/src/vec3.h
        02_Motion_Blur/src/main.cpp
)

set(    SOURCE_BOOK_2_PROJ_03
        03_BVH/src/camera.h
        03_BVH/src/color.h
        03_BVH/src/hittable.h
        03_BVH/src/hittable_list.h
        03_BVH/src/material.h
        03_BVH/src/ray.h
        03_BVH/src/rtweekend.h
        03_BVH/src/sphere.h
        03_BVH/src/vec3.h
        03_BVH/src/aabb.h
        03_BVH/src/bvh.h
        03_BVH/src/main.cpp
        )

set(    SOURCE_BOOK_2_PROJ_04
        03_BVH/src/camera.h
        03_BVH/src/color.h
        03_BVH/src/hittable.h
        03_BVH/src/hittable_list.h
        03_BVH/src/material.h
        03_BVH/src/ray.h
        03_BVH/src/rtweekend.h
        03_BVH/src/sphere.h
        03_BVH/src/vec3.h
        03_BVH/src/aabb.h
        03_BVH/src/bvh.h
        03_BVH/src/main.cpp
        )


#[[
set(    SOURCE_BOOK_2_PROJ_08
        02_Motion_Blur/src/camera.h
        02_Motion_Blur/src/color.h
        02_Motion_Blur/src/hittable.h
        02_Motion_Blur/src/hittable_list.h
        02_Motion_Blur/src/material.h
        02_Motion_Blur/src/ray.h
        02_Motion_Blur/src/rtweekend.h
        02_Motion_Blur/src/sphere.h
        02_Motion_Blur/src/vec3.h
        02_Motion_Blur/src/main.cpp
)
]]

# Executables

add_executable(02_Motion_Blur ${SOURCE_BOOK_2_PROJ_02})
add_executable(03_BVH ${SOURCE_BOOK_2_PROJ_03})
add_executable(04_Solid_Textures ${SOURCE_BOOK_2_PROJ_04})
#[[add_executable(04_Diffuse_Materials ${SOURCE_BOOK_2_PROJ_04})
add_executable(05_Metal ${SOURCE_BOOK_2_PROJ_05})
add_executable(06_Dielectrics-Glass ${SOURCE_BOOK_2_PROJ_06})
add_executable(07_Camera ${SOURCE_BOOK_2_PROJ_07})
add_executable(02_Motion_Blur ${SOURCE_BOOK_2_PROJ_08})
]]


message(STATUS "PROJECT_BINARY_DIR: ${PROJECT_BINARY_DIR}")
message(STATUS "PROJECT_SOURCE_DIR: ${PROJECT_SOURCE_DIR}")


