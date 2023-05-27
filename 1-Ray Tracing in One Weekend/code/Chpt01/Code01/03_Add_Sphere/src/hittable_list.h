#pragma once
#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

#include "hittable.h"

#include <memory>
#include <vector>
#include <algorithm>
#include <typeinfo>

using std::shared_ptr;
using std::make_shared;

bool isSomethingHit = false;


class hittable_list : public hittable
{

	public:
		std::vector<shared_ptr<hittable>> objects;

        std::vector<shared_ptr<hittable>>::iterator curIter;

	public:
		hittable_list() {}
		hittable_list(shared_ptr <hittable> object) { add(object); }

		void clear() { objects.clear(); }
		void add(shared_ptr<hittable> object) { objects.push_back(object); }
//        std::vector<shared_ptr<hittable>>::iterator find(shared_ptr<hittable> target)
        bool find(shared_ptr<hittable> target)
        {
            std::vector<shared_ptr<hittable>>::iterator iter = std::find(objects.begin(), objects.end(), target);
            if (iter != objects.end()) {
                curIter = iter;
                std::cerr << "hittable_list::find() : iter == " << iter->get() << std::endl;

                return true;
            }


            return false;
        }

		virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const override;

};


hittable_list objectsHitDetected;

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

            const std::type_info& info_id = typeid(object);
            auto typeName = info_id.name();
            std::cerr << "target is a " << typeName << std::endl;

            auto objGet = object.get();
            std::cerr << "the object is a " << objGet << std::endl;

            if (!objectsHitDetected.find(object))
            {
                objectsHitDetected.add(object);
            }
		}
	}
	
	return hit_anything;
}



#endif