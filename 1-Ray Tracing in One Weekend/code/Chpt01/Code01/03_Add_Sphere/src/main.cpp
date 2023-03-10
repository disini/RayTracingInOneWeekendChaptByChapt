

//#include <stdio.h>
//#include <stdlib.h>

#include "rtweekend.h"
#include "color.h"
#include "hittable_list.h"
#include "ray.h"
#include "sphere.h"
#include "camera.h"


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

//color ray_color(const ray& r)
color ray_color(const ray& r, const hittable& world)
{
	
	//if (hit_sphere(point3(0, 0, -1), 0.5, r))
	//if (hit_sphere(point3(-1, 0, -2), 0.5, r))
		//return color(1, 0, 0);// 球形内部统一为红色
	/*
	auto t = hit_sphere(point3(0, 0, -1), 0.5, r);// 计算光线r与球形的碰撞点的r的t值
	if (t > 0.0)
	{
		vec3 N = unit_vector(r.at(t) - vec3(0, 0, -1));// 得到t值对应坐标点的球的法线
		return 0.5*color(N.x() + 1, N.y() + 1, N.z() + 1);// (-1, 1) --> (0, 1)， 根据法线的值得到不同的颜色，渐变色
	}
	*/

	hit_record rec;
	if (world.hit(r, 0, infinity, rec))
	{
		return 0.5 * (rec.normal + color(1, 1, 1));
	}
				
	vec3 unit_direction = unit_vector(r.direction());
	auto t = 0.5 * (unit_direction.y() + 1.0);// (-1, 1) --> (0, 1)
	return (1.0 - t) * color(1.0, 1.0, 1.0) + t * color(0.5, 0.7, 1.0);// 球形外部随着y值变化而为线性渐变色
}


int main()
{
	// Image
	const auto aspect_ratio = 16.0 / 9.0;
	const int image_width = 400;
	const int image_height = static_cast<int>(image_width /aspect_ratio);
	const int samples_per_pixel = 100;

	// World(Objects)
	hittable_list world;
	world.add(make_shared<sphere>(point3(0, 0, -1), 0.5));// small sphere on the top
	world.add(make_shared<sphere>(point3(0, -100.5, -1), 100));// big sphere at the bottom
	//world.add(make_shared<sphere>(point3(0, -100.6, -1), 100.6));// big sphere at the bottom


	// Camera
	/*
	auto viewport_height = 2.0;
	auto viewport_width = aspect_ratio * viewport_height;
	auto focal_length = 1.0;

	auto origin = point3(0, 0, 0);
	auto horizontal = vec3(viewport_width, 0, 0);
	auto vertical = vec3(0, viewport_height, 0);
	auto lower_left_corner = origin - horizontal / 2 - vertical / 2 - vec3(0, 0, focal_length);
	*/
	camera cam;
	
	// Render

	std::cout << "P3\n" << image_width << " " << image_height << "\n255\n";
	for (int j = image_height -1; j >= 0; --j)
	{
		std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush << '\n';		
	
			
		for (int i = 0; i < image_width ;++i)
		{
			//if (i > 180)// 仅部分列（columns）绘制
			//{
			//	write_color(std::cout, color(0, 0, 0));
			//}
			//else
			//{
				color pixel_color(0, 0, 0);
				for (int s=0; s < samples_per_pixel;++s)
				{
					//auto u = double(i) / (image_width - 1);// 单一采样
					//auto v = double(j) / (image_height - 1);
					auto u = (i + random_double()) / (image_width - 1);// 随机多重采样				
					auto v = (j + random_double()) / (image_height - 1);						

					//auto b = 0.25;
					//ray r(origin, lower_left_corner + u * horizontal + v * vertical - origin);
					// //color pixel_color(double(i) / (image_width-1), double(j)/(image_height-1), 0.25);
					ray r = cam.get_ray(u, v);

					/*int ir = static_cast<int>(255.999 * r);
					int ig = static_cast<int>(255.999 * g);
					int ib = static_cast<int>(255.999 * b);*/

					// //color pixel_color = ray_color(r);
					//color pixel_color = ray_color(r, world);
					pixel_color += ray_color(r, world);
				}

				//write_color(std::cout, pixel_color);
				write_color(std::cout, pixel_color, samples_per_pixel);

				//std::cout << ir << " " << ig << " " << ib << "\n";

				/*if (i > 500)
				{
					system("pause");
				}*/

			//}
					
		}

		//if ( j <= image_height - 6)// 仅部分行（rows）绘制
		//{
		//	return 0;
		//}
	}

	std::cerr << "\nDone.\n";

	return 0;
}