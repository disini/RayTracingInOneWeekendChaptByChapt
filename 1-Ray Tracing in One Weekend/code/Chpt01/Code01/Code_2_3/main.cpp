// Code_2_3.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
//#include <stdio.h>
//#include <stdlib.h>
#include "color.h"



int main()
{
	// Image
	
	int image_width = 256;
	int image_height = 256;
	
	// Render

	std::cout << "P3\n" << image_width << " " << image_height << "\n255\n";
	for (int j = image_height -1; j >= 0; j--)
	{
		std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush << '\n';		
	
			
		for (int i = 0; i < image_width ;i++)
		{
			/*auto r = double(i) / (image_width);
			auto g = double(j) / (image_height);
			auto b = 0.25;*/

			color pixel_color(double(i) / (image_width-1), double(j)/(image_height-1), 0.25);

			/*int ir = static_cast<int>(255.999 * r);
			int ig = static_cast<int>(255.999 * g);
			int ib = static_cast<int>(255.999 * b);*/

			write_color(std::cout, pixel_color);

			//std::cout << ir << " " << ig << " " << ib << "\n";

			/*if (i > 500)
			{
				system("pause");
			}*/
		}
	}

	std::cerr << "\nDone.\n";

	return 0;
}