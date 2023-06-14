//
// Created by liusheng on 2023/6/9.
//

#ifndef PERLIN_H
#define PERLIN_H

#include "rtweekend.h"


class perlin {
public:
    perlin() {
        ranfloat = new double[point_count];
        for (int i = 0; i < point_count; ++i) {
            ranfloat[i] = random_double();// random float number between 0 and 1
        }

        perm_x = perlin_generate_perm();
        perm_y = perlin_generate_perm();
        perm_z = perlin_generate_perm();

    }


    ~perlin() {
        delete[] ranfloat;
        delete[] perm_x;
        delete[] perm_y;
        delete[] perm_z;
    }

    //check the ranfloat array get a grey scale value according to the coordinates of point p
    double noise(const point3& p) const {
        auto i = static_cast<int>(16 * p.x()) & 255;
        auto j = static_cast<int>(16 * p.y()) & 255;
        auto k = static_cast<int>(16 * p.z()) & 255;// prevent for overflow

        return ranfloat[perm_x[i] ^ perm_y[j] ^ perm_z[k]];
    }






private:
    static const int point_count = 256;
    double* ranfloat;
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




    static void permute(int* p, int n) {//Ëæ»ú´òÂÒË³Ğò
        for (int i = n - 1; i > 0; --i) {
            int target = random_int(0, i);
            int tmp = p[i];
            p[i] = p[target];
            p[target] = tmp;
        }
    }



};


#endif //CODE02_PERLIN_H
