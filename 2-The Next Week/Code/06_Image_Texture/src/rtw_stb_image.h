//
// Created by liusheng on 2023/6/15.
//

#ifndef RTWEEKNED_STB_IMAGE_H
#define RTWEEKNED_STB_IMAGE_H

// Disable pedantic warnings for this external library.
#ifdef _MSC_VER
// Microsoft Visuall C++ Compiler
    #pragma warning (push, 0)
#endif


#define STB_IMAGE_IMPLEMENTATION
#include "external/stb_image.h"

// Restore warning levels.
#ifdef _MSC_VER
// Microsoft Visuall C++ Compiler
    #pragma warning (pop)
#endif


#endif //CODE02_RTW_STB_IMAGE_H
