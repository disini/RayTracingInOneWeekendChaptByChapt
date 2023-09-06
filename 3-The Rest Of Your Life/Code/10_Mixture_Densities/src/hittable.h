#pragma once

#ifndef HITTABLE_H
#define HITTABLE_H

#include "ray.h"
#include "aabb.h"
#include "rtweekend.h"

class material;

struct hit_record
{
	point3 p;// position of the hit point
	vec3 normal;
	shared_ptr<material> mat_ptr;
	double t;
    double u;
    double v;
	bool front_face = true;

	inline void set_face_normal(const ray& r, const vec3& outward_normal)
	{
		front_face = dot(r.direction(), outward_normal) < 0;
		normal = front_face ? outward_normal : -outward_normal;
	}

};

class hittable
{
public:
	virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const = 0;
    virtual bool bounding_box(double time0, double time1, aabb& output_box) const = 0;
    virtual double pdf_value(const point3& o, const vec3& v) const {
        return 0.0;
    }

    virtual vec3 random(const vec3& o) const {
        return vec3(1, 0, 0);
    }
};



// translate an object
class translate : public hittable {
    public:
        translate(shared_ptr<hittable> ptr, const vec3& displacement) : hittable_obj_ptr(ptr), offset(displacement) {}

        virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const override;

        virtual  bool bounding_box(double time0, double time1, aabb& output_box) const override;


    public:
        shared_ptr<hittable> hittable_obj_ptr;
        vec3 offset;
};

bool translate::hit(const ray &r, double t_min, double t_max, hit_record& rec) const {
    ray moved_ray(r.origin() - offset, r.direction(), r.time());

    if (!hittable_obj_ptr->hit(moved_ray, t_min, t_max, rec))
        return false;

    rec.p += offset;
    rec.set_face_normal(moved_ray, rec.normal);

    return true;
}

bool translate::bounding_box(double time0, double time1, aabb &output_box) const {
    if (!hittable_obj_ptr->bounding_box(time0, time1, output_box))
        return false;

    output_box = aabb(output_box.min() + offset,
                      output_box.max() + offset);

    return true;
}

// rotate an object
class rotate_y : public hittable {
    public:
        rotate_y(shared_ptr<hittable>ptr, double angle);

    virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const override;
    virtual bool bounding_box(double time0, double time1, aabb& output_box) const override {
        output_box = bbox;
        return hasbox;
    }



    public:
        shared_ptr<hittable> hittable_obj_ptr;
        double sin_theta;
        double cos_theta;
        bool hasbox;
        aabb bbox;

};

// Rotate-Y rotate method
rotate_y::rotate_y(shared_ptr<hittable> ptr, double angle) : hittable_obj_ptr(ptr) {
    auto radians = degrees_to_radians(angle);
    sin_theta = sin(radians);
    cos_theta = cos(radians);
    hasbox = hittable_obj_ptr->bounding_box(0, 1, bbox);

    point3 min(infinity, infinity, infinity);
    point3 max(infinity, infinity, infinity);

    for(int i = 0; i < 2;++i)
    {
        for (int j = 0; j < 2; ++j) {
            for (int k = 0; k < 2; ++k) {
                auto x = i * bbox.max().x() + (1-i) * bbox.min().x();
                auto y = j * bbox.max().y() + (1-j) * bbox.min().y();
                auto z = j * bbox.max().z() + (1-k) * bbox.min().z();

                auto newX = cos_theta * x + sin_theta * z;
                auto newZ = -sin_theta * x + cos_theta * z;

                vec3 tester(newX, y, newZ);

                for (int c = 0; c < 3; ++c) {
                    min[c] = fmin(min[c], tester[c]);
                    max[c] = fmax(max[c], tester[c]);
                }
            }
        }
    }

    bbox = aabb(min, max);
}

bool rotate_y::hit(const ray& r, double t_min, double t_max, hit_record& rec) const {
    auto origin = r.origin();
    auto direction = r.direction();

    origin[0] = cos_theta * r.origin()[0] - sin_theta * r.origin()[2];// x
    origin[2] = sin_theta * r.origin()[0] + cos_theta * r.origin()[2]; // z

    direction[0] = cos_theta * r.direction()[0] - sin_theta * r.direction()[2];// x
    direction[2] = sin_theta * r.direction()[0] + cos_theta * r.direction()[2]; // z

    ray rotated_ray(origin, direction, r.time());

    if (!hittable_obj_ptr->hit(rotated_ray, t_min, t_max, rec))
        return false;

    auto pos = rec.p;
    auto normal = rec.normal;

    pos[0] = cos_theta * rec.p[0] + sin_theta * rec.p[2];
    pos[2] = -sin_theta * rec.p[0] + cos_theta * rec.p[2];

    normal[0] = cos_theta * rec.normal[0] + sin_theta * rec.normal[2];
    normal[2] = -sin_theta * rec.normal[0] + cos_theta * rec.normal[2];

    rec.p = pos;
    rec.set_face_normal(rotated_ray, normal);

    return true;
}

class flip_face : public hittable {
    public:
        flip_face(shared_ptr<hittable> p) : ptr(p) {}

        virtual bool hit(
                const ray& r, double t_min, double t_max, hit_record& rec) const override {
            if (!ptr->hit(r, t_min, t_max, rec))
                return false;

            rec.front_face = !rec.front_face;
            return true;
        }

        virtual bool bounding_box(double time0, double time1, aabb& outputbox) const override {
            return ptr->bounding_box(time0, time1, outputbox);
        }

    public:
        shared_ptr<hittable> ptr;
};



#endif

