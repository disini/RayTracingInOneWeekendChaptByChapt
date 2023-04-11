#pragma once

#ifndef RTWEEKEND_H
#define RTWEEKEND_H

#include <cmath>
#include <limits>
#include <memory>
#include <cstdlib>
#include <random>

// Common Headers

#include "ray.h"
#include "vec3.h"
//#include <time.h>// https://blog.csdn.net/qq_42939980/article/details/124879760
//#include <cstdlib>
//#include <ctime>// http://c.biancheng.net/view/1352.html

// Usings

using std::shared_ptr;
using std::make_shared;
using std::sqrt;

// Constants

const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

// Utility Functions

double random_double();


inline double degrees_to_radians(double degrees)
{
	return degrees * pi / 180.0;
}

//inline double random_double()
//{
//	// Returns a random real in [0, 1).
//	return rand() / (RAND_MAX + 1.0);
//}

inline double random_double()
{
	// Returns a random real in [0, 1).
	//return rand() / (RAND_MAX + 1.0);
	double result;

	result = rand() / (RAND_MAX + 1.0);
	return result;
}


/*
//inline double random_double()
double random_double()
{
	//srand((unsigned)time(NULL));// https://blog.csdn.net/qq_42939980/article/details/124879760
	
	// http://c.biancheng.net/view/1352.html
	unsigned seed;// Random generator seed
	double result;
	seed = time(0);// 从“time_t”转换到“unsigned int”，可能丢失数据
	srand(seed);
	// Returns a random real in [0, 1).
	//return rand() / (RAND_MAX + 1.0);
	auto rand_Value = rand();
	//result = rand() / (RAND_MAX + 1.0);
	//result = rand_Value / (RAND_MAX + 1.0);// 32767 + 1 = 32768
	//result = double(rand_Value % 100) / 100;//
	result = double(rand_Value % 100) / 101;//
	//result = double(rand_Value % 99) / 101;//
	return result;
}
*/

inline double random_double(double min, double max)
{
	// Returns a random real in [min, max).
	return min + (max - min) * random_double();
}

inline double clamp(double x, double min, double max)
{
	if (x < min)
	{
		return min;
	}
	if (x > max)
	{
		return max;
	}
	return x;
}

//
//inline double random_double()
//{	
//	static std::uniform_real_distribution<double> distribution(0.0, 1.0);
//	static std::mt19937 generator;
//	return distribution(generator);
//}

#endif



