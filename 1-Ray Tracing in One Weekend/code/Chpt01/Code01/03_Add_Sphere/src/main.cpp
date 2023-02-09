// Code_2_3.cpp : This file contains the 'main' function. Program execution begins and ends there.
//


//#include <stdio.h>
//#include <stdlib.h>
#include "color.h"
#include "ray.h"


#include <iostream>

//bool hit_sphere(const point3& center, double radius, const ray& r) 
/*double hit_sphere(const point3& center, double radius, const ray& r) // before denominator '2' extracted
{
	vec3 oc = r.origin() - center;
	auto a = dot(r.direction(), r.direction());
	auto b = 2.0 * dot(oc, r.direction());
	auto c = dot(oc, oc) - radius * radius;
	auto discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
	{
		return -1.0;
	}
	else
	{
		return (-b - sqrt(discriminant)) / (2.0 * a);
	}


	//return (discriminant > 0);
}
*/

double hit_sphere(const point3& center, double radius, const ray& r)// after denominator '2' extracted
{
	vec3 oc = r.origin() - center;
	auto a = r.direction().length_squared();// r^2
	//auto b = 2.0 * dot(oc, r.direction());
	auto half_b = dot(oc, r.direction());
	//auto c = dot(oc, oc) - radius * radius;
	auto c = oc.length_squared() - radius * radius;
	//auto discriminant = b * b - 4 * a * c;
	auto discriminant = half_b * half_b - a * c;// equal 1/4 former discriminant
	if (discriminant < 0)
	{
		return -1.0;
	}
	else
	{
		//return (-b - sqrt(discriminant)) / (2.0 * a);// before denominator '2.0' extracted
		return (-half_b - sqrt(discriminant)) / a;// after denominator '2.0' extracted
	}


	//return (discriminant > 0);
}

color ray_color(const ray& r)
{
	
	//if (hit_sphere(point3(0, 0, -1), 0.5, r))
	//if (hit_sphere(point3(-1, 0, -2), 0.5, r))
		//return color(1, 0, 0);// �����ڲ�ͳһΪ��ɫ
	auto t = hit_sphere(point3(0, 0, -1), 0.5, r);// �������r�����ε���ײ���r��tֵ
	if (t > 0.0)
	{
		vec3 N = unit_vector(r.at(t) - vec3(0, 0, -1));// �õ�tֵ��Ӧ��������ķ���
		return 0.5*color(N.x() + 1, N.y() + 1, N.z() + 1);// (-1, 1) --> (0, 1)�� ���ݷ��ߵ�ֵ�õ���ͬ����ɫ������ɫ
	}
			
	vec3 unit_direction = unit_vector(r.direction());
	t = 0.5 * (unit_direction.y() + 1.0);// (-1, 1) --> (0, 1)
	return (1.0 - t) * color(1.0, 1.0, 1.0) + t * color(0.5, 0.7, 1.0);// �����ⲿ����yֵ�仯��Ϊ���Խ���ɫ
}


int main()
{
	// Image
	const auto aspect_ratio = 16.0 / 9.0;
	const int image_width = 400;
	const int image_height = static_cast<int>(image_width /aspect_ratio);

	// Camera
	auto viewport_height = 2.0;
	auto viewport_width = aspect_ratio * viewport_height;
	auto focal_length = 1.0;

	auto origin = point3(0, 0, 0);
	auto horizontal = vec3(viewport_width, 0, 0);
	auto vertical = vec3(0, viewport_height, 0);
	auto lower_left_corner = origin - horizontal / 2 - vertical / 2 - vec3(0, 0, focal_length);
	
	// Render

	std::cout << "P3\n" << image_width << " " << image_height << "\n255\n";
	for (int j = image_height -1; j >= 0; j--)
	{
		std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush << '\n';		
	
			
		for (int i = 0; i < image_width ;i++)
		{
			//if (i > 180)// �������У�columns������
			//{
			//	write_color(std::cout, color(0, 0, 0));
			//}
			//else
			//{
						
				auto u = double(i) / (image_width - 1);
				auto v = double(j) / (image_height - 1);
				//auto b = 0.25;
				ray r(origin, lower_left_corner + u * horizontal + v * vertical - origin);
				//color pixel_color(double(i) / (image_width-1), double(j)/(image_height-1), 0.25);

				/*int ir = static_cast<int>(255.999 * r);
				int ig = static_cast<int>(255.999 * g);
				int ib = static_cast<int>(255.999 * b);*/

				color pixel_color = ray_color(r);

				write_color(std::cout, pixel_color);

				//std::cout << ir << " " << ig << " " << ib << "\n";

				/*if (i > 500)
				{
					system("pause");
				}*/

			//}
					
		}

		//if ( j < image_height - 180)// �������У�rows������
		//{
		//	return 0;
		//}
	}

	std::cerr << "\nDone.\n";

	return 0;
}