#pragma once

#ifndef COLOR_H
#define COLOR_H

#include "vec3.h"

#include <iostream>


void write_color(std::ostream& out, color pixel_color)
{
	// Write the translated [0, 255] value of each color component.
	out << static_cast<int>(255.999 * pixel_color.x()) << ' '
		<< static_cast<int>(255.999 * pixel_color.y()) << ' '
		<< static_cast<int>(255.999 * pixel_color.z()) << '\n';


}

void write_color(std::ostream& out, color pixel_color, int samples_per_pixel)
{
	auto r = pixel_color.x();
	auto g = pixel_color.y();
	auto b = pixel_color.z();

    // Replace NaN components with zero. See explanation in Ray Tracing : The Rest of Your Life.
    if (r != r)
    {
        std::cerr << "color::write_color(), r is NaN!" << std::endl;
        r = 0.0;
    }
    if (g != g)
    {
        std::cerr << "color::write_color(), g is NaN!" << std::endl;
        g = 0.0;
    }
    if (b != b)
    {
        std::cerr << "color::write_color(), b is NaN!" << std::endl;
        b = 0.0;
    }

	// // Divide the color by the number of samples.
	// Divide the color by the number of samples and gamma-correct for gamma = 2.0. so the power 1/gamma = 1/2, means a square root.
	auto scale = 1.0 / samples_per_pixel;
	/*r *= scale;
	g *= scale;
	b *= scale;*/
	r = sqrt(scale * r);
	g = sqrt(scale * g);
	b = sqrt(scale * b);

	// Write the translated [0, 255] value of each color component.
	out << static_cast<int>(256 * clamp(r, 0.0, 0.999)) << ' '
		<< static_cast<int>(256 * clamp(g, 0.0, 0.999)) << ' '
		<< static_cast<int>(256 * clamp(b, 0.0, 0.999)) << '\n';
}



#endif