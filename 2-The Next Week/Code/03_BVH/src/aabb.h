//
// Created by liusheng on 23-4-17.
//

#pragma once

#ifndef AABB_H
#define AABB_H


#include "rtweekend.h"

class aabb {
    public:


    point3 minimum;
    point3 maximum;

    aabb() {}
    aabb(const point3& a, const point3& b) { minimum = a; maximum =b;}

    point3 min() const {return minimum;}
    point3 max() const {return maximum;}

    bool hit(const ray& r, double t_min, double t_max) const {
        for (int a = 0; a < 3; a++) {
            auto t0 = fmin((minimum[a] - r.origin()[a])/r.direction()[a],
                            (maximum[a] - r.origin()[a])/r.direction()[a]);
            auto t1 = fmax((minimum[a] - r.origin()[a])/r.direction()[a],
                           (maximum[a] - r.origin()[a])/r.direction()[a]);
            t_min = fmax(t0, t_min);
            t_max = fmin(t1, t_max);// 缩小区间范围
            if(t_max < t_min)
                return false;
        }

        return true;
    }












};


/*
// An Optimized AABB Hit Method by Andrew Kensler at Pixar
inline bool aabb::hit(const ray& r, double t_min, double t_max) const {
    for (int a = 0; a < 3; a++) {
        auto invD = 1.0f/r.direction()[a];// 单位方向矢量
        auto t0 = (min()[a] - r.origin()[a]) * invD;
        auto t1 = (max()[a] - r.origin()[a]) * invD;
        if(invD < 0.0f)// 方向
            std::swap(t0, t1);
        t_min = t0 > t_min ? t0 : t_min;
        t_max = t1 < t_max ? t1 : t_max;// 缩小区间范围
        if(t_max <= t_min)
            return false;
    }
    return true;
}
*/


aabb surrounding_box(aabb box0, aabb box1) {
    point3  small(fmin(box0.min().x(), box1.min().x()),
                  fmin(box0.min().y(), box1.min().y()),
                  fmin(box0.min().z(), box1.min().z()));

    point3 big(fmax(box0.max().x(), box1.max().x()),
               fmax(box0.max().y(), box1.max().y()),
               fmax(box0.max().z(), box1.max().z()));

    return aabb(small, big);
}































#endif //PETER_SHIRLEY_AABB_H
