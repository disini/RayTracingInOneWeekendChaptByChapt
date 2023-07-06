//
// Created by liusheng on 2/7/2023.
//

#include "rtweekend.h"

#include <iostream>
#include <iomanip>
#include <math.h>
#include <stdlib.h>


int calc_pi_1() {
    int N = 1000;
    int inside_circle = 0;
    for (int i = 0; i < N; ++i) {
        auto x = random_double(-1, 1);
        auto y = random_double(-1, 1);
        if (x*x + y*y < 1)
            inside_circle++;
    }

    double area_ratio = double(inside_circle) / N;
    std::cout << std::fixed << std::setprecision(12);// Estimate of Pi = 3.088000000000
    std::cout << "Estimate of Pi = " << 4 * area_ratio << "\n";// Estimate of Pi = 3.088
    //
    return 0;
}

int calc_pi_2() {
    int inside_circle = 0;
    int runs = 0;
    std::cout << std::fixed << std::setprecision(12);
    while(true)
    {
        runs++;
        auto x = random_double(-1, 1);
        auto y = random_double(-1, 1);

        if (x*x + y*y < 1)
            inside_circle++;

        if (runs % 100000 == 0)
            std::cout << "Estimate of Pi = "
                      << 4*double(inside_circle) / runs
                      << ", runs = "
                      << runs
                      << "\n";

        if (runs > 1000000)
            return 1;
    }
    return 0;
}



int calc_pi_2_1(unsigned long long endCount = 100000000) {
    unsigned long long inside_circle = 0;
//    const int endCount = 100000000;// 1亿
    unsigned long long runs = 0;
    std::cout << std::fixed << std::setprecision(12);
    while(true)
    {
        runs++;
        auto x = random_double(-1, 1);
        auto y = random_double(-1, 1);

        if (x*x + y*y < 1)
            inside_circle++;

//        if (runs % endCount == 0)
        if (runs >= endCount)
        {
            std::cout << "Estimate of Pi = "
                      << 4*double(inside_circle) / double(runs)
                      << ", runs = "
                      << runs
                      << "\n";

            return 1;
        }



    }

    return 0;
}



int calc_pi_3() {
    int inside_circle = 0;
    int inside_circle_stratified = 0;
    int sqrt_N = 10000;
    int runs = 0;
    std::cout << std::fixed << std::setprecision(12);
    for(int i = 0; i < sqrt_N;i++)
    {
        for (int j = 0; j < sqrt_N; ++j)
        {
            runs++;
            auto x = random_double(-1, 1);
            auto y = random_double(-1, 1);

            if (x*x + y*y < 1)
                inside_circle++;

            x = 2 * ((i + random_double()) / sqrt_N) - 1;// 2*(0, 1) - 1 --> (0, 1);
            y = 2 * ((j + random_double()) / sqrt_N) - 1;

            if (x*x + y*y < 1)
                inside_circle_stratified++;

        }
    }

    auto N = sqrt_N * sqrt_N;

//    if (runs % 100000 == 0)
        std::cout << "Regular   Estimate of Pi = "
                  << 4 * double(inside_circle) / N << "\n"
                  << "Stratified    Estimate of Pi = "
                  << 4 * double(inside_circle_stratified) / N << "\n"
                  << ", runs = "
                  << runs
                  << "\n";

//    if (runs > 1000000)
        return 0;

}

int calc_pi_3_1(long sqrt_N = 10000) {
    unsigned long long inside_circle = 0;
//    int sqrt_N = 10000;
    unsigned long long N = sqrt_N * sqrt_N;
    unsigned long long  runs = 0;
    std::cout << std::fixed << std::setprecision(16);
    for(long i = 0; i < sqrt_N;i++)
    {
        for (long j = 0; j < sqrt_N; ++j)
        {
            runs++;
           if (i*i + j*j < N)
                inside_circle++;

        }
    }

//    if (runs % 100000 == 0)
    std::cout << "Estimate of Pi = "
              << 4 * double(inside_circle) / double (N) << "\n"
              << ", inside_circle = "
              << inside_circle
              << ", runs = "
              << runs
              << "\n";

//    if (runs > 1000000)
    return 0;

}




int main()  {
//    calc_pi_1();//Estimate of Pi = 3.088000000000

//    calc_pi_2();
    //Estimate of Pi = 3.143760000000, runs = 100000
//    Estimate of Pi = 3.143840000000, runs = 200000
//    Estimate of Pi = 3.143626666667, runs = 300000
//    Estimate of Pi = 3.142310000000, runs = 400000
//    Estimate of Pi = 3.141344000000, runs = 500000
//    Estimate of Pi = 3.143693333333, runs = 600000
//    Estimate of Pi = 3.143720000000, runs = 700000
//    Estimate of Pi = 3.143230000000, runs = 800000
//    Estimate of Pi = 3.143888888889, runs = 900000
//    Estimate of Pi = 3.142872000000, runs = 1000000

//    calc_pi_2_1();
    // Estimate of Pi = 3.141744840000, runs = 100000000

//    calc_pi_2_1(1000000000);// 10亿次
//    Estimate of Pi = 3.141576212000, runs = 1000000000

    calc_pi_2_1(10000000000);// 100亿次
//    Estimate of Pi = 3.141573872000, runs = 10000000000


//    calc_pi_3();
//    Regular   Estimate of Pi = 3.141514800000
//    Stratified    Estimate of Pi = 3.141589480000
//    , runs = 100000000

//    calc_pi_3_1();
    // Estimate of Pi = 3.141990160000
    //, runs = 100000000

//    calc_pi_3_1(100000);
    // Estimate of Pi = 0.564026163200
    //, runs = 1410065408

//    Estimate of Pi = 3.1416325411999999
//    , inside_circle = 7854081353, runs = 10000000000



    return 0;
}











