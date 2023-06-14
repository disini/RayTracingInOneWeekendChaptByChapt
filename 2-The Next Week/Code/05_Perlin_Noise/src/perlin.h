//
// Created by liusheng on 2023/6/9.
//

#ifndef PERLIN_H
#define PERLIN_H

#include "rtweekend.h"


class perlin {
public:
    perlin() {
//        ranfloat = new double[point_count];
        ranvec = new vec3[point_count];
        for (int i = 0; i < point_count; ++i) {
//            ranfloat[i] = random_double();// random float number between 0 and 1
            ranvec[i] = unit_vector(vec3::random(-1, 1));
        }

        perm_x = perlin_generate_perm();
        perm_y = perlin_generate_perm();
        perm_z = perlin_generate_perm();

    }


    ~perlin() {
//        delete[] ranfloat;
        delete[] ranvec;
        delete[] perm_x;
        delete[] perm_y;
        delete[] perm_z;
    }

    //check the ranfloat array get a grey scale value according to the coordinates of point p
    double noise0(const point3& p) const {
        auto i = static_cast<int>(16 * p.x()) & 255;
        auto j = static_cast<int>(16 * p.y()) & 255;
        auto k = static_cast<int>(16 * p.z()) & 255;// prevent for overflow

        return ranfloat[perm_x[i] ^ perm_y[j] ^ perm_z[k]];
    }



    //check the ranfloat array get a grey scale value according to the coordinates of point p
    double noise1(const point3& p) const {
        // remove the integer part, then u, v, w are all less than 1
        auto u = p.x() - floor(p.x());
        auto v = p.y() - floor(p.y());
        auto w = p.z() - floor(p.z());

        u = u*u*(3-2*u);
        v = v*v*(3-2*v);
        w = w*w*(3-2*w);

        auto i = static_cast<int>(floor(p.x()));
        auto j = static_cast<int>(floor(p.y()));
        auto k = static_cast<int>(floor(p.z()));// prevent for overflow
        double c[2][2][2];

        for (int di = 0; di < 2; ++di) {
            for (int dj = 0; dj < 2; ++dj) {
                for (int dk = 0; dk < 2; ++dk) {
                    c[di][dj][dk] = ranfloat[
                            perm_x[(i + di) & 255] ^
                            perm_x[(j + dj) & 255] ^
                            perm_x[(k + dk) & 255]
                    ];
                }
            }
        }

//        return ranfloat[perm_x[i] ^ perm_y[j] ^ perm_z[k]];
        return trilinear_interp(c, u, v, w);
    }

    //check the ranfloat array get a grey scale value according to the coordinates of point p
    double noise(const point3& p) const {
        // remove the integer part, then u, v, w are all less than 1
        auto u = p.x() - floor(p.x());
        auto v = p.y() - floor(p.y());
        auto w = p.z() - floor(p.z());

        auto i = static_cast<int>(floor(p.x()));
        auto j = static_cast<int>(floor(p.y()));
        auto k = static_cast<int>(floor(p.z()));// prevent for overflow
//        double c[2][2][2];
        vec3 c[2][2][2];

        for (int di = 0; di < 2; ++di) {
            for (int dj = 0; dj < 2; ++dj) {
                for (int dk = 0; dk < 2; ++dk) {
                    c[di][dj][dk] = ranvec[
                            perm_x[(i + di) & 255] ^
                            perm_x[(j + dj) & 255] ^
                            perm_x[(k + dk) & 255]
                    ];
                }
            }
        }

//        return ranfloat[perm_x[i] ^ perm_y[j] ^ perm_z[k]];
//        return trilinear_interp(c, u, v, w);
        return perlin_interp(c, u, v, w);
    }




private:
    static const int point_count = 256;
    double* ranfloat;
    vec3* ranvec;
    int* perm_x;
    int* perm_y;
    int* perm_z;

    static int* perlin_generate_perm() {
        auto p = new int[point_count];
        for (int i = 0; i < point_count; ++i)
        {
            p[i] = i;// fill the array
        }
        permute(p, point_count);// reorder the elements randomly

        return p;
    }




    static void permute(int* p, int n) {//Ëæ»ú´òÂÒË³Ðò
        for (int i = n - 1; i > 0; --i) {
            int target = random_int(0, i);
            int tmp = p[i];
            p[i] = p[target];
            p[target] = tmp;
        }
    }

    static double trilinear_interp(double c[2][2][2], double u, double v, double w)
    {
        auto accum = 0.0;//ÀÛ¼ÓÆ÷£¨accumulator£©
        for (int i = 0; i < 2; ++i) {
            for (int j = 0; j < 2; ++j) {
                for (int k = 0; k < 2; ++k) {
                    accum += (i*u + (1-i)*(1-u))*
                             (j*v + (1-j)*(1-v))*
                             (k*w + (1-k)*(1-w)) * c[i][j][k];
                }
            }
        }

        return accum;
    }

    static double perlin_interp(vec3 c[2][2][2], double u, double v, double w)
    {
        auto uu = u*u*(3-2*u);
        auto vv = v*v*(3-2*v);
        auto ww = w*w*(3-2*w);

        auto accum = 0.0;

        for (int i = 0; i < 2; ++i) {
            for (int j = 0; j < 2; ++j) {
                for (int k = 0; k < 2; ++k) {
                    vec3 weight_v(u-i, v-j, w-k);
                    accum += (i*uu + (1-i)*(1-uu))
                           * (j*vv + (1-j)*(1-vv))
                           * (k*ww + (1-k)*(1-ww))
                           * dot(c[i][j][k], weight_v);
                }
            }
        }

        return accum;

    }



};


#endif //CODE02_PERLIN_H
