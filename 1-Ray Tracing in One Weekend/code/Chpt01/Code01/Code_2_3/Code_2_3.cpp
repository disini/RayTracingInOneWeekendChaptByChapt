// Code_2_3.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
//#include <stdio.h>
//#include <stdlib.h>



int main()
{
	int nx = 200;
	int ny = 100;
	std::cout << "P3\n" << nx << " " << ny << "\n255\n";
	for (int j = ny - 1; j >= 0; j--)
	{
		std::cerr << "r\Scanlines remaining: " << j << ' ' << std::flush << '\n';		
		for (int i = 0; i < nx; i++)
		{
			float r = float(i) / float(nx);
			float g = float(j) / float(ny);
			float b = 0.2;

			int ir = int(255.99 * r);
			int ig = int(255.99 * g);
			int ib = int(255.99 * b);

			std::cout << ir << " " << ig << " " << ib << "\n";

			/*if (i > 500)
			{
				system("pause");
			}*/
		}
	}

	std::cerr << "\nDone.\n";

	return 0;
}