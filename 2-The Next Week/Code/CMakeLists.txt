cmake_minimum_required( VERSION 3.1.0 )

project( Code01
        VERSION 3.0.0
        LANGUAGES CXX
)

# Set to c++11
set(CMAKE_CXX_STANDARD 11)

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

#[[
add_executable(03_Add_Sphere ${SOURCE_BOOK_2_PROJ_03})
add_executable(04_Diffuse_Materials ${SOURCE_BOOK_2_PROJ_04})
add_executable(05_Metal ${SOURCE_BOOK_2_PROJ_05})
add_executable(06_Dielectrics-Glass ${SOURCE_BOOK_2_PROJ_06})
add_executable(07_Camera ${SOURCE_BOOK_2_PROJ_07})
add_executable(02_Motion_Blur ${SOURCE_BOOK_2_PROJ_08})
]]
