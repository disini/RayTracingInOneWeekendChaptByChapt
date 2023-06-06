//
// Created by liusheng on 23-5-28.
//

#ifndef TEXTURE_H
#define TEXTURE_H

#include "rtweekend.h"

class texture {
    public:
        virtual color value(double u, double v, const point3& p) const =0;
};

class solid_color : public texture {
    public:
        solid_color() {}
        solid_color(color c) : color_value(c) {}

        solid_color(double red, double green, double blue)
            : solid_color(color(red, green, blue)) {}

            virtual color value(double u, double v, const point3& p) const override {
            return color_value;
        }




    private:
        color color_value;


};


class checker_texture : public texture{
    public:


        checker_texture() {}

        checker_texture(shared_ptr<texture> _even, shared_ptr<texture> _odd)
            : even(_even), odd(_odd) {}

        checker_texture(color c1, color c2)
            : even(make_shared<solid_color>(c1)), odd(make_shared<solid_color>(c2)) {}

        virtual color value(double u, double v, const point3& p) const override {
            auto sines = sin(10*p.x()) * sin(10*p.y()) * sin(10*p.z());
            if (sines < 0)
                return odd->value(u, v, p);
            else
                return even->value(u,v, p);
        }


    public:
        shared_ptr<texture> odd;
        shared_ptr<texture> even;

};


class tiled_random_texture : public texture {
    public:

        tiled_random_texture() {}

        virtual color value(double u, double v, const point3& p) const override {
            auto sines = sin(10*p.x()) * sin(10*p.y()) * sin(10*p.z());
            int index_X = floorf(3*(1 + sin(10*p.x())));
            int index_Y = floorf(3*(1 + sin(10*p.y())));
            int index_Z = floorf(3*(1 + sin(10*p.z())));


            return color(indexed_color[index_X], indexed_color[index_Y], indexed_color[index_Z]);
        }


    private:
        float indexed_color[6] = {0.1, 0.32, 0.19, 0.78, 0.43, 0.86};

};




#endif //CODE02_TEXTURE_H
