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
        04_Solid_Textures/src/camera.h
        04_Solid_Textures/src/color.h
        04_Solid_Textures/src/hittable.h
        04_Solid_Textures/src/hittable_list.h
        04_Solid_Textures/src/material.h
        04_Solid_Textures/src/ray.h
        04_Solid_Textures/src/rtweekend.h
        04_Solid_Textures/src/sphere.h
        04_Solid_Textures/src/vec3.h
        04_Solid_Textures/src/aabb.h
        04_Solid_Textures/src/bvh.h
        04_Solid_Textures/src/main.cpp
        04_Solid_Textures/src/texture.h
    )

set(    SOURCE_BOOK_2_PROJ_05
        05_Perlin_Noise/src/camera.h
        05_Perlin_Noise/src/color.h
        05_Perlin_Noise/src/hittable.h
        05_Perlin_Noise/src/hittable_list.h
        05_Perlin_Noise/src/material.h
        05_Perlin_Noise/src/ray.h
        05_Perlin_Noise/src/rtweekend.h
        05_Perlin_Noise/src/sphere.h
        05_Perlin_Noise/src/vec3.h
        05_Perlin_Noise/src/aabb.h
        05_Perlin_Noise/src/bvh.h
        05_Perlin_Noise/src/main.cpp
        05_Perlin_Noise/src/texture.h
        05_Perlin_Noise/src/perlin.h
    )

set(
        SOURCE_BOOK_2_PROJ_06
        06_Image_Texture/src/external/stb_image.h
        06_Image_Texture/src/camera.h
        06_Image_Texture/src/color.h
        06_Image_Texture/src/hittable.h
        06_Image_Texture/src/hittable_list.h
        06_Image_Texture/src/material.h
        06_Image_Texture/src/ray.h
        06_Image_Texture/src/rtweekend.h
        06_Image_Texture/src/sphere.h
        06_Image_Texture/src/vec3.h
        06_Image_Texture/src/aabb.h
        06_Image_Texture/src/bvh.h
        06_Image_Texture/src/main.cpp
        06_Image_Texture/src/texture.h
        06_Image_Texture/src/perlin.h
        06_Image_Texture/src/rtw_stb_image.h
    )

set(
        SOURCE_BOOK_2_PROJ_07
        07_Rectangles_and_Lights/src/external/stb_image.h
        07_Rectangles_and_Lights/src/camera.h
        07_Rectangles_and_Lights/src/color.h
        07_Rectangles_and_Lights/src/hittable.h
        07_Rectangles_and_Lights/src/hittable_list.h
        07_Rectangles_and_Lights/src/material.h
        07_Rectangles_and_Lights/src/ray.h
        07_Rectangles_and_Lights/src/rtweekend.h
        07_Rectangles_and_Lights/src/sphere.h
        07_Rectangles_and_Lights/src/vec3.h
        07_Rectangles_and_Lights/src/aabb.h
        07_Rectangles_and_Lights/src/bvh.h
        07_Rectangles_and_Lights/src/main.cpp
        07_Rectangles_and_Lights/src/texture.h
        07_Rectangles_and_Lights/src/perlin.h
        07_Rectangles_and_Lights/src/rtw_stb_image.h
        07_Rectangles_and_Lights/src/aarect.h)


set(
        SOURCE_BOOK_2_PROJ_08
        08_Instances/src/external/stb_image.h
        08_Instances/src/camera.h
        08_Instances/src/color.h
        08_Instances/src/hittable.h
        08_Instances/src/hittable_list.h
        08_Instances/src/material.h
        08_Instances/src/ray.h
        08_Instances/src/rtweekend.h
        08_Instances/src/sphere.h
        08_Instances/src/vec3.h
        08_Instances/src/aabb.h
        08_Instances/src/bvh.h
        08_Instances/src/main.cpp
        08_Instances/src/texture.h
        08_Instances/src/perlin.h
        08_Instances/src/rtw_stb_image.h
        08_Instances/src/aarect.h 08_Instances/src/box.h)



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
add_executable(05_Perlin_Noise ${SOURCE_BOOK_2_PROJ_05})
add_executable(06_Image_Texture ${SOURCE_BOOK_2_PROJ_06})
add_executable(07_Rectangles_and_Lights ${SOURCE_BOOK_2_PROJ_07})
add_executable(08_Instances ${SOURCE_BOOK_2_PROJ_08})
#[[add_executable(04_Diffuse_Materials ${SOURCE_BOOK_2_PROJ_04})
add_executable(05_Metal ${SOURCE_BOOK_2_PROJ_05})
add_executable(06_Dielectrics-Glass ${SOURCE_BOOK_2_PROJ_06})
add_executable(07_Camera ${SOURCE_BOOK_2_PROJ_07})
add_executable(02_Motion_Blur ${SOURCE_BOOK_2_PROJ_08})
]]


message(STATUS "PROJECT_BINARY_DIR: ${PROJECT_BINARY_DIR}")
message(STATUS "PROJECT_SOURCE_DIR: ${PROJECT_SOURCE_DIR}")


