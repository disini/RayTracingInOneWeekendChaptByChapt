#pragma once

#ifndef MOVING_SPHERE_H
#define MOVING_SPHERE_H


#include "hittable.h"
#include "vec3.h"

class moving_sphere : public hittable
{
	public:
		point3 center0, center1;
        double time0, time1 = 0.0;
		double radius = 0.0;
		shared_ptr<material> mat_ptr;


	public:
        moving_sphere() {};
        moving_sphere(point3 cen0, point3 cen1, double _time0, double _time1, double r, shared_ptr<material> m)
		: center0(cen0), center1(cen1), time0(_time0), time1(_time1), radius(r), mat_ptr(m) {};
		
		virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const override;

        point3 center(double time) const;

};

point3 moving_sphere::center(double time) const {
    return center0 + ((time - time0)/(time1 - time0)) * (center1 - center0);
}

bool moving_sphere::hit(const ray& r, double t_min, double t_max, hit_record& rec) const {
//	vec3 oc = r.origin() - center;
	vec3 oc = r.origin() - center(r.time());
	auto a = r.direction().length_squared();
	auto half_b = dot(oc, r.direction());
	auto c = oc.length_squared() - radius * radius;

	auto discriminant = half_b * half_b - a * c;
	if (discriminant < 0) return false;
	auto sqrtd = sqrt(discriminant);

	// Find the nearest root that lies in the acceptable range.
	auto root = (-half_b - sqrtd) / a;
	if (root < t_min || t_max < root)
	{
		root = ( - half_b + sqrtd) / a;
		if (root < t_min || root > t_max)
			return false;
	}

	rec.t = root;
	rec.p = r.at(rec.t);
	//rec.normal = (rec.p - center) / radius;
//	vec3 outward_normal = (rec.p - center) / radius;
	vec3 outward_normal = (rec.p - center(r.time())) / radius;
	rec.set_face_normal(r, outward_normal);//determinate the normal direction inner or outward by calculate the dot.
	rec.mat_ptr = mat_ptr;

	return true;
}


#endif
