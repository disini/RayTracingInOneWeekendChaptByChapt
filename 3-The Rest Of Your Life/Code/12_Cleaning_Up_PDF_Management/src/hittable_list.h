#pragma once
#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

#include "hittable.h"
#include "aabb.h"

#include <memory>
#include <vector>

using namespace std;

//using std::shared_ptr;
//using std::make_shared;


class hittable_list : public hittable
{

	public:
		std::vector<shared_ptr<hittable>> objects;

	public:
		hittable_list() {}
		hittable_list(shared_ptr <hittable> object) { add(object); }

		void clear() { objects.clear(); }
		void add(shared_ptr<hittable> object) { objects.push_back(object); }

        shared_ptr<hittable> getObjByName(const string name);

		virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const override;
        virtual bool bounding_box(double time0, double time1, aabb& output_box) const override;
        virtual double pdf_value(const vec3 &o, const vec3 &v) const override;
};


bool hittable_list::hit(const ray& r, double t_min, double t_max, hit_record& rec) const
{
	hit_record temp_rec;
	bool hit_anything = false;
	auto closest_so_far = t_max;

	for (const auto& object : objects)
	{
		if (object->hit(r, t_min, closest_so_far, temp_rec))
		{
			hit_anything = true;
			closest_so_far = temp_rec.t;
			rec = temp_rec;
		}
	}
	
	return hit_anything;
}

bool hittable_list::bounding_box(double time0, double time1, aabb &output_box) const {
    if (objects.empty()) return false;

    aabb temp_box;
    bool first_box = true;

    for (const auto& object:objects) {
        if (!object->bounding_box(time0, time1, temp_box)) return false;
        output_box = first_box ? temp_box : surrounding_box(output_box, temp_box);
        first_box = false;
    }

    return true;
}

double hittable_list::pdf_value(const point3 &o, const vec3 &v) const {
    auto weight = 1.0/objects.size();
    auto sum = 0.0;

    for (const auto& object : objects)
    {
        sum += weight * object->pdf_value(o, v);
    }

    return sum;
}

shared_ptr<hittable> hittable_list::getObjByName(const string name){
    for (const auto& object : objects) {
        if (object->getName() == name)
        {
            return object;
        }
    }

//    auto newObj = make_shared<xzerect>()
    return objects.at(0);

}


#endif