//
// Created by liusheng on 23-5-28.
//

#ifndef TEXTURE_H
#define TEXTURE_H

#include "rtweekend.h"

using namespace std;

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
                return even->value(u, v, p);
        }


    public:
        shared_ptr<texture> odd;
        shared_ptr<texture> even;

};


class tiled_random_texture : public texture {
    public:

        tiled_random_texture() {}

        virtual color value(double u, double v, const point3& p) const override {
//            auto sines = sin(10*p.x()) * sin(10*p.y()) * sin(10*p.z());
//
//            int index_X = floorf(3*(1 + sin(10*p.x())));
//            int index_Y = floorf(3*(1 + sin(10*p.y())));
//            int index_Z = floorf(3*(1 + sin(10*p.z())));

            auto sinX = sin(p.x());
            auto sinY = sin(p.y());
            auto sinZ = sin(p.z());

//            int index_X = floorf(3*(1 + sin(p.x())));
//            int index_Y = floorf(3*(1 + sin(p.y())));
//            int index_Z = floorf(3*(1 + sin(p.z())));

            int index_X = floorf(3*(0.99 + sinX));
            int index_Y = floorf(3*(0.99 + sinY));
            int index_Z = floorf(3*(0.99 + sinZ));

//            if (index_X < 0 || index_X > 5)
            if (index_X < 0)
            {
//                system->pause();
                index_X = 0;
            }

            if (index_Y < 0)
            {
                index_Y = 0;
            }

            if (index_Z < 0)
            {
                index_Z = 0;
            }


//            if (index_X < 0 || index_X > 5)
            if (index_X > 5)
            {
//                system->pause();
                std::cerr << "index_X == " << index_X << endl;
            }

            if (index_Y > 5)
            {
                std::cerr << "index_Y == " << index_Y << endl;
            }

            if (index_Z > 5)
            {
                std::cerr << "index_Z == " << index_Z << endl;
            }

//            return color(indexed_color[index_X], indexed_color[index_Y], indexed_color[index_Z]);

            float grey = indexed_color[index_X] * indexed_color[index_Y] * indexed_color[index_Z];
            return color(grey, grey, grey);
        }


    private:
        float indexed_color[6] = {0.6, 0.82, 0.49, 0.78, 0.43, 0.96};

};


class tiled_random_texture1 : public texture {
public:

    tiled_random_texture1() {}

    size_t segmentNum = sizeof(indexed_color)/sizeof(indexed_color[0]);//
//    int len;
//    ARR_LEN(arr, len);

    virtual color value(double u, double v, const point3& p) const override {

//
//            int index_X = int(p.x()) % 6;
//            if ((p.x() > -1) && (p.x()) < 0)
//                index_X = 5;
//
//            int index_Y = int(p.y()) % 6;
//            if ((p.y() > -1) && (p.y()) < 0)
//                index_Y = 5;
//
//            int index_Z = int(p.z()) % 6;
//            if ((p.z() > -1) && (p.z()) < 0)
//                index_Z = 5;

        double pX = 10 * p.x();
        double pY = 10 * p.y();
        double pZ = 10 * p.z();

        int index_X = int(pX) % 6;
        if ((pX > -1) && (pX) < 0)
            index_X = 5;

        int index_Y = int(pY) % 6;
        if ((pY > -1) && (pY) < 0)
            index_Y = 5;

        int index_Z = int(pZ) % 6;
        if ((pZ > -1) && (pZ) < 0)
            index_Z = 5;



//        int num1 = int(-1.23); // -1
//        int num2 = int(-1.23) % 6;  // -1
//
//        int num3 = int(-0.98);  // 0
//        int num4 = int(-0.98) % 6; // 0
//
//        int num5 = int(-0.23); // 0
//        int num6 = int(-0.23) % 6; // 0



//        int index_X = p.x() < 0 ? int(p.x() + 6) % 6 : int(p.x()) % 6;
//        int index_Y = p.y() < 0 ? int(p.y() + 6) % 6 : int(p.y()) % 6;
//        int index_Z = p.z() < 0 ? int(p.z() + 6) % 6 : int(p.z()) % 6;



//        int index_X = int(10 * p.x()) % 6;
//        int index_Y = int(10 * p.y()) % 6;
//        int index_Z = int(10 * p.z()) % 6;


//        auto sinX = sin(p.x());
//        auto sinY = sin(p.y());
//        auto sinZ = sin(p.z());

//            int index_X = floorf(3*(1 + sin(p.x())));
//            int index_Y = floorf(3*(1 + sin(p.y())));
//            int index_Z = floorf(3*(1 + sin(p.z())));

//        int index_X = floorf(3*(0.99 + sinX));
//        int index_Y = floorf(3*(0.99 + sinY));
//        int index_Z = floorf(3*(0.99 + sinZ));

//        if (index_X < 0 || index_X > 5)
        if (index_X < 0)
        {
//                system->pause();
            index_X += 5;
        }

//        if (index_Y < 0 || index_Y > 5)
        if (index_Y < 0)
        {
            index_Y += 5;
        }

//        if (index_Z < 0 || index_Z > 5)
        if (index_Z < 0)
        {
            index_Z += 5;
        }
//
//
////            if (index_X < 0 || index_X > 5)
//        if (index_X > 5)
//        {
////                system->pause();
//            std::cerr << "index_X == " << index_X << endl;
//        }
//
//        if (index_Y > 5)
//        {
//            std::cerr << "index_Y == " << index_Y << endl;
//        }
//
//        if (index_Z > 5)
//        {
//            std::cerr << "index_Z == " << index_Z << endl;
//        }

//            return color(indexed_color[index_X], indexed_color[index_Y], indexed_color[index_Z]);

//        float grey = indexed_color[index_X] * indexed_color[index_Y] * indexed_color[index_Z];
        float grey = indexed_color[index_X] * indexed_color[6-index_Y] * indexed_color[index_Z];


        return color(grey, grey, grey);
    }


private:
    float indexed_color[6] = {0.6, 0.12, 0.49, 0.78, 0.43, 0.96};
//    const int segment = 6;

};



#endif //CODE02_TEXTURE_H
