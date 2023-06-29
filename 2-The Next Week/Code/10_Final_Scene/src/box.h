//
// Created by liusheng on 23Äê6ÔÂ24ÈÕ.
//

#ifndef BOX_H
#define BOX_H

#include "rtweekend.h"
#include "aarect.h"
#include "hittable_list.h"

class box:public hittable {
public:
    box() {}
    box(const point3& p0, const point3& p1, shared_ptr<material> mat_ptr);

    virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const override {
        return sides.hit(r, t_min, t_max, rec);
    }

    virtual bool bounding_box(double time0, double time1 ,aabb& output_box) const override {
        output_box = aabb(box_min, box_max);
        return true;
    }

public:
    point3 box_min;
    point3 box_max;
    hittable_list sides;


};

box::box(const point3& p0, const point3& p1, shared_ptr<material> mat_ptr) {
    box_min = p0;
    box_max = p1;

    sides.add(make_shared<xy_rect>(p0.x(), p1.x(), p0.y(), p1.y(), p1.z(), mat_ptr));// front
    sides.add(make_shared<xy_rect>(p0.x(), p1.x(), p0.y(), p1.y(), p0.z(), mat_ptr));// back

    sides.add(make_shared<xz_rect>(p0.x(), p1.x(), p0.z(), p1.z(), p1.y(), mat_ptr));// top
    sides.add(make_shared<xz_rect>(p0.x(), p1.x(), p0.z(), p1.z(), p0.y(), mat_ptr));// bottom

    sides.add(make_shared<yz_rect>(p0.y(), p1.y(), p0.z(), p1.z(), p1.x(), mat_ptr));// right
    sides.add(make_shared<yz_rect>(p0.y(), p1.y(), p0.z(), p1.z(), p0.x(), mat_ptr));// left

/*
    bool::hit(const ray& r, double t_min, double t_max, hit_record& rec) const {
        return sides.hit(r, t_min, t_max, rec);
    }
    */




}









#endif //CODE02_BOX_H
