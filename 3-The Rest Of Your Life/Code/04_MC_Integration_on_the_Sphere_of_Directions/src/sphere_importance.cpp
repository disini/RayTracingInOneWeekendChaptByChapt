//
// Created by liusheng on 5/7/2023.
//

#include "rtweekend.h"


#include <iostream>
#include <iomanip>
//#include <math.h>
//#include <stdlib.h>



inline double pdf(const vec3& p) {
    return 1 / (4*pi);
}

// Generating importance-sampled points on the unit sphere
int main() {
    int N = 1000000;
    auto sum = 0.0;
    for (int i = 0; i < N; ++i) {
        vec3 d = random_unit_vector();
        auto cosine_squared = d.z()* d.z();
        sum += cosine_squared / pdf(d);
    }

    std::cout << std::fixed << std::setprecision(12);
    std::cout << "I = " << sum/N << "\n";

    return 0;
}

// I = 4.180370661880 (4/3 * pi)













