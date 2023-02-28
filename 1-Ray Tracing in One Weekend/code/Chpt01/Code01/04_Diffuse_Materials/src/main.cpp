

//#include <stdio.h>
//#include <stdlib.h>

//#include "../../common/rtweekend.h"
#include "vec3.h"
#include "rtweekend.h"
#include "color.h"
#include "hittable_list.h"
#include "ray.h"
#include "sphere.h"
#include "camera.h"


#include <iostream>


double hit_sphere(const point3& center, double radius, const ray& r)// after denominator '2' extracted
{
	vec3 oc = r.origin() - center;
	auto a = r.direction().length_squared();// r^2
	auto half_b = dot(oc, r.direction());
	auto c = oc.length_squared() - radius * radius;
	auto discriminant = half_b * half_b - a * c;// equal 1/4 former discriminant
	if (discriminant < 0)
	{
		return -1.0;
	}
	else
	{
		return (-half_b - sqrt(discriminant)) / a;// after denominator '2.0' extracted
	}

}

color ray_color(const ray& r, const hittable& world)
{
	

	hit_record rec;
	vec3 vec;
	if (world.hit(r, 0, infinity, rec))
	{
		//return 0.5 * (rec.normal + color(1, 1, 1));
		point3 target = rec.p + rec.normal + random_in_unit_sphere();
		//point3 target = rec.p + rec.normal + vec.random_in_unit_sphere();
		//point3 target = rec.p + rec.normal + vec3::random_in_unit_sphere();
		return 0.5 * ray_color(ray(rec.p, target - rec.p), world);
	}
				
	vec3 unit_direction = unit_vector(r.direction());
	auto t = 0.5 * (unit_direction.y() + 1.0);// (-1, 1) --> (0, 1)
	return (1.0 - t) * color(1.0, 1.0, 1.0) + t * color(0.5, 0.7, 1.0);// 球形外部随着y值变化而为线性渐变色
}

color ray_color(const ray& r, const hittable& world, int depth)
{
	hit_record rec;
	vec3 vec;

	// If we've exceeded the ray bounce limit, no more light is gathered.
	if (depth <= 0)
		return color(0, 0, 0);// black!
	
	
	if (world.hit(r, 0, infinity, rec))
	{
		//return 0.5 * (rec.normal + color(1, 1, 1));
		point3 target = rec.p + rec.normal + random_in_unit_sphere();
		//point3 target = rec.p + rec.normal + vec.random_in_unit_sphere();
		//point3 target = rec.p + rec.normal + vec3::random_in_unit_sphere();
		return 0.5 * ray_color(ray(rec.p, target - rec.p), world, depth - 1);
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
	const int max_depth = 50;

	// World(Objects)
	hittable_list world;
	world.add(make_shared<sphere>(point3(0, 0, -1), 0.5));// small sphere on the top
	world.add(make_shared<sphere>(point3(0, -100.5, -1), 100));// big sphere at the bottom
	//world.add(make_shared<sphere>(point3(0, -100.6, -1), 100.6));// big sphere at the bottom


	// Camera
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
					auto u = (i + random_double()) / (image_width - 1);// 随机多重采样				
					auto v = (j + random_double()) / (image_height - 1);						

					ray r = cam.get_ray(u, v);

					//pixel_color += ray_color(r, world);
					pixel_color += ray_color(r, world, max_depth);
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