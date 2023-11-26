#pragma once

#ifndef RTWEEKEND_H
#define RTWEEKEND_H

#include <cmath>
#include <limits>
#include <memory>

// Common Headers

#include "ray.h"
#include "vec3.h"

// Usings

using std::shared_ptr;
using std::make_shared;
using std::sqrt;

// Constants

const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

// Utility Funcitons

inline double degrees_to_radians(double degrees)
{
	return degrees * pi / 180.0;
}




#endif



