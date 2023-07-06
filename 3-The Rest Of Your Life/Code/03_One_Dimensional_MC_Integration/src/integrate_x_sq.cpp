//
// Created by liusheng on 2/7/2023.
//
#include "rtweekend.h"

#include <iostream>
#include <iomanip>
#include <math.h>
#include <stdlib.h>

// Integrating x^2
double integrating_1(double start = 0, double end = 2)
{
    int N = 1000000;
    double I = 0;
    auto sum = 0.0;
    for (int i = 0; i < N; ++i) {
        auto x = random_double(0, 2);
        sum += x*x;
    }

    I = 2 * sum/N;
    std::cout << std::fixed << std::setprecision(12);
    std::cout << "integrating_1() : I = " << I << "\n";// I=2⋅average(x^2,0,2)

    return I;
}

//  probability density function
inline double pdf(double x)
{
    return 0.5 * x;
}

inline double pdf2(double x)
{
    return 0.5;
}

inline double pdf3(double x)
{
    return 3*x*x / 8;
}


// Integrating x^2 with PDF
double integrating_2(double start = 0, double end = 2)
{
    int N = 1000000;
    double I = 0;
    auto sum = 0.0;
    for (int i = 0; i < N; ++i) {
        auto x = sqrt(random_double(0, 4));
        sum += x*x / pdf(x);
    }

    I = sum/N;
    std::cout << std::fixed << std::setprecision(12);
    std::cout << "integrating_2() : I = " << I << "\n";// I=2⋅average(x^2,0,2)

    return I;
}


// Integrating x^2, v3, with uniform samples PDF
double integrating_3(double start = 0, double end = 2)
{
    int N = 1000000;
    double I = 0;
    auto sum = 0.0;
    for (int i = 0; i < N; ++i) {
        auto x = sqrt(random_double(0, 4));
        sum += x * x / pdf2(x);
    }

    I = sum/N;
    std::cout << std::fixed << std::setprecision(12);
    std::cout << "integrating_3() : I = " << I << "\n";// I=2⋅average(x^2,0,2)

    return I;
}

// Integrating x^2, v4, final version
double integrating_4(double start = 0, double end = 2)
{
    int N = 1;
    double I = 0;
    auto sum = 0.0;
    for (int i = 0; i < N; ++i) {
        auto x = pow(random_double(0, 8), 1.0/3.0);
        sum += x * x / pdf3(x);
    }

    I = sum/N;
    std::cout << std::fixed << std::setprecision(12);
    std::cout << "integrating_4() : I = " << I << "\n";// I=2⋅average(x^2,0,2)

    return I;
}


int main() {

    double result1 = integrating_1();
    std::cout << "result1 * 3 = " << result1 * 3  <<  "\n\n";
//    I = 2.666462964444
//    result1 * 3 = 7.999388893333

    double result2 = integrating_2();
    std::cout << "result2 * 3 = " << result2 * 3  <<  "\n\n";
//    I = 2.666687175806
//    result2 * 3 = 8.000061527417

    double result3 = integrating_3();
    std::cout << "result3 * 3 = " << result3 * 3  <<  "\n\n";
//    integrating_3() : I = 3.999587602230
//    result3 * 3 = 11.998762806691


    double result4 = integrating_4();
    std::cout << "result4 * 3 = " << result4 * 3  <<  "\n\n";
//    integrating_4() : I = 2.666666666667
//    result3 * 3 = 8.000000000000 // exactly the analytically result!


    return 0;
}
