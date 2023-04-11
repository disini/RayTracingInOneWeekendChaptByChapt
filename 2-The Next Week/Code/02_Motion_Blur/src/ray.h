#pragma once

#ifndef RAY_H
#define RAY_H

#include "vec3.h"

class ray
{
public:
	point3 orig;
	vec3 dir;
    double tm;

public:
	ray() {}
	ray(const point3& origin, const vec3& direction, double time = 0.0)
		: orig(origin), dir(direction), tm(time)
	{}

	point3 origin() const { return orig; }
	vec3 direction() const { return dir; }
    double time() const {return tm;}


	point3 at(double t) const // 根据t值返回该处的坐标值
	{
		return orig + t * dir;
	}






};

#endif