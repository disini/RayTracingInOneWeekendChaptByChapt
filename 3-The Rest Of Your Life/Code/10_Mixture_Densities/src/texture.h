//
// Created by liusheng on 23-5-28.
//

#ifndef TEXTURE_H
#define TEXTURE_H

#include "rtweekend.h"
#include "rtw_stb_image.h"
#include "perlin.h"

#include <iostream>

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

    size_t segmentNum = sizeof(indexed_color) / sizeof(indexed_color[0]);//
//    int len;
//    ARR_LEN(arr, len);

    virtual color value(double u, double v, const point3 &p) const override {

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
        if (index_X < 0) {
//                system->pause();
            index_X += 5;
        }

//        if (index_Y < 0 || index_Y > 5)
        if (index_Y < 0) {
            index_Y += 5;
        }

//        if (index_Z < 0 || index_Z > 5)
        if (index_Z < 0) {
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
        float grey = indexed_color[index_X] * indexed_color[6 - index_Y] * indexed_color[index_Z];


        return color(grey, grey, grey);
    }

private:
    float indexed_color[6] = {0.6, 0.12, 0.49, 0.78, 0.43, 0.96};
};

    class tiled_random_texture2 : public texture {
    public:

        tiled_random_texture2() {
            generateRandomColors();
        }



        virtual color value(double u, double v, const point3& p) const override {

            const int scale = 4;

            double pX = scale * p.x();
            double pY = scale * p.y();
            double pZ = scale * p.z();

            int index_X = int(pX) % 6;
            if ((pX > -1) && (pX) < 0)
                index_X = 5;

            int index_Y = int(pY) % 6;
            if ((pY > -1) && (pY) < 0)
                index_Y = 5;

            int index_Z = int(pZ) % 6;
            if ((pZ > -1) && (pZ) < 0)
                index_Z = 5;

            if (index_X < 0)
            {
//                system->pause();
                index_X += 5;
            }

            if (index_Y < 0)
            {
                index_Y += 5;
            }

            if (index_Z < 0)
            {
                index_Z += 5;
            }


            float grey = indexed_3d_color[index_X][index_Y][index_Z];


            return color(grey, grey, grey);
        }


    private:
        float indexed_color[6] = {0.6, 0.12, 0.49, 0.78, 0.43, 0.96};
    //    const int segment = 6;
        float indexed_3d_color[6][6][6] = {};

    private:
        bool generateRandomColors() {
            for(int i = 0; i < 6; i++)
            {
                for(int j = 0; j < 6; j++)
                {
                    for(int k = 0; k < 6; k++)
                    {
                        indexed_3d_color[i][j][k] = random_double(0.01, 0.99);
                    }
                }
            }

            return true;
        }



};


    class noise_texture : public texture {
        public:
            noise_texture() {}
            noise_texture(double sc) : scale(sc) {}

            virtual color value(double u, double v, const point3& p) const override
            {
//                return color(1, 1, 1) * noise.noise(p);
//                return color(1, 1, 1) * noise.noise(scale * p);
//                return color(1, 1, 1) * 0.5 * (1 + noise.noise(scale * p));// (-1, 1) --> (0, 1)
//                return color(1, 1, 1) * noise.turb(scale * p);// Commenting out straight noise and turbulence

                // take turbulence as an additional item.
                return color(1, 1, 1) * 0.5 * (1 + sin(scale * p.z() + 10 * noise.turb(p)));
            }



    public:
        perlin noise;
        double scale;

    };





    class image_texture : public texture {
    public:
        const static int bytes_per_pixel = 3;

        image_texture()
            : data(nullptr), width(0), height(0), bytes_per_scanline(0) {}

        image_texture(const char* filename) {
                auto components_per_pixel = bytes_per_pixel;

                data = stbi_load(
                    filename, &width ,&height, &components_per_pixel, components_per_pixel);

                if(!data) {
                    std::cerr << "ERROR : Could not load texture image file '" << filename << "' .\n";
                    width = height = 0;
                }

                    bytes_per_scanline = bytes_per_pixel * width;
        }


        ~image_texture() {
            delete data;
        }

        virtual color value(double u, double v, const vec3& p) const override {
            //If we have no texture data, then return solid cyan as a debugging aid.
            if(data == nullptr)
            {
                return color(0, 1, 1);
            }

        // Clamp input texture coordinates to [0,1] x [1,0]
            u = clamp(u, 0.0, 1.0);
            v = 1.0 - clamp(v, 0.0, 1.0); // Flip V to image coordinates (up to bottom --flip--> bottom to up)

            auto i = static_cast<int>(u * width);
            auto j = static_cast<int>(v * height);

            // Clamp integer mapping, since actual coordinates should be less than 1.0
            if(i > width) i = width;
            if(j > height) j = height;

            const auto color_scale = 1.0 / 255.0;//(0, 255) --> (0, 1)
            auto pixel = data + j * bytes_per_scanline + i * bytes_per_pixel;

            return color(color_scale*pixel[0], color_scale*pixel[1], color_scale*pixel[2]);
            // pixel[0], pixel[1], pixel[2] are between (0, 255)
        }


    private:
        unsigned char* data;
        int width, height;
        int bytes_per_scanline;






    };




#endif //CODE02_TEXTURE_H
