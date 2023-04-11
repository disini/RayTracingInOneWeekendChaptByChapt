#pragma once

#ifndef VEC3_H
#define VEC3_H

#include <cmath>
#include <iostream>

//#include "../../common/rtweekend.h"
//#include "rtweekend.h"

using std::sqrt;

double random_double();
double random_double(double min, double max);

class vec3
{
public: 
	vec3() : e{0, 0, 0} {}
	vec3(double e0, double e1, double e2) : e{ e0, e1, e2 } {}

	double x()const { return e[0]; }
	double y()const { return e[1]; }
	double z()const { return e[2]; }

	vec3 operator-() const { return vec3(-e[0], -e[1], -e[2]); }
	double operator[](int i) const { return e[i]; }
	double& operator[](int i) { return e[i]; }

	vec3& operator+=(const vec3& v) {
		e[0] += v.e[0];
		e[1] += v.e[1];
		e[2] += v.e[2];
		return *this;
	}

	vec3& operator*= (const double t) {
		e[0] *= t;
		e[1] *= t;
		e[2] *= t;
		return *this;
	}

	vec3& operator/=(const double t) {
		return *this *= 1/t;
	}

	double length() const {
		return sqrt(length_squared());
	}
	

	double length_squared() const {
		return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];
	}

	bool near_zero() const
	{
		// Return true if the vector is close to zero in all dimensions.
		const auto s = 1e-8;
		// fabs(float x) or  fabs(double x): 求浮点数x的绝对值
		return (fabs(e[0]) < s) && (fabs(e[1]) < s)&& (fabs(e[2]) < s);
	}


	


	inline static vec3 random()
	{
		return vec3(random_double(), random_double(), random_double());
	}

	inline static vec3 random(double min, double max)
	{
		return vec3(random_double(min, max), random_double(min, max), random_double(min, max));
	}

	//inline static vec3 random_in_unit_sphere()
	


public:
	double e[3];


};

// Type aliases for vec3
using point3 = vec3; // 3D point
using color = vec3; // RGB color

inline std::ostream& operator<<(std::ostream& out, const vec3& v) 
{
	return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2];
}

inline vec3 operator+(const vec3& u, const vec3& v)
{
	return vec3(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]);
}

inline vec3 operator-(const vec3& u, const vec3& v)
{
	return vec3(u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2]);
}

inline vec3 operator*(const vec3& u, const vec3& v)
{
	return vec3(u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]);
}


inline vec3 operator*(double t, const vec3& v)
{
	return vec3(t * v.e[0], t * v.e[1], t * v.e[2]);
}

inline vec3 operator*(const vec3& v, double t)
{
	return t * v;
}


inline vec3 operator/(const vec3& v, double t)
{
	return (1 / t) * v;
}

inline double dot(const vec3& u, const vec3& v)
{
	return u.e[0] * v.e[0]
		+ u.e[1] * v.e[1]
		+ u.e[2] * v.e[2];
}

inline vec3 cross(const vec3& u, const vec3& v)
{
	return vec3(u.e[1] * v.e[2] - u.e[2] * v.e[1],
				u.e[2] * v.e[0] - u.e[0] * v.e[2],
				u.e[0] * v.e[1] - u.e[1] * v.e[0]);
}

inline vec3 unit_vector(vec3 v)
{
	return v / v.length();
}

vec3 random_in_unit_disk()// 返回单位圆盘内的一个随机点坐标
{
	while (true)
	{
		auto p = vec3(random_double(-1, 1), random_double(-1, 1), 0);
		if (p.length_squared() >= 1)
			continue;
		return p;	
	}
}

inline vec3 random_in_unit_sphere()
{
	while (true)
	{
		auto p = vec3::random(-1, 1);
		double lengthSquare = p.length_squared();
		//if (p.length_squared() >= 1)
		if (lengthSquare >= 1)
			continue;
		
		return p;
	}
}

// non - unit length-- > unit length vector
vec3 random_unit_vector() 
{
	return unit_vector(random_in_unit_sphere());


}

vec3 random_in_hemisphere(const vec3& normal)
{
	vec3 in_unit_sphere = random_in_unit_sphere();
	if (dot(in_unit_sphere, normal) > 0.0) // In the same hemisphere as the normal
		return in_unit_sphere;
	else
		return -in_unit_sphere;
}




//inline vec3 reflect(const vec3& v, const vec3& n) // Same as the books
//inline static vec3 reflect(const vec3& v, const vec3& n)
vec3 reflect(const vec3& v, const vec3& n)
{
	return v - 2 * dot(v, n) * n;
	// B == dot(v, -N) * N,  v + 2B == v + 2*(dot(v, -N)) * N  == v - 2*dot(v, N)* N, N is unit normal!
}

/**
* @brief 计算折射光线
* @param uv 入射光线,也就是书中的R
* @param n 入射面法线
* @param etai_over_etat 出射介质与入射介质相对折射率

*/
//************************************
// Method:    refract
// FullName:  refract
// Access:    public 
// Returns:   vec3
// Qualifier:
// Parameter: const vec3 & uv
// Parameter: const vec3 & n
// Parameter: double etai_over_etat
//************************************
vec3 refract(const vec3& uv, const vec3& n, double etai_over_etat)
{
	auto cos_theta = fmin(dot(-uv, n), 1.0);
	vec3 r_out_perp = etai_over_etat * (uv + cos_theta * n);// 出射光线的垂直于入射面法线的分量 : R′⊥
	vec3 r_out_parallel = -sqrt(fabs(1.0 - r_out_perp.length_squared())) *n;// 出射光线的平行于入射面法线的分量 : R'||

	return r_out_perp + r_out_parallel;// 合成 : R' = R′⊥ + R'||
}








#endif