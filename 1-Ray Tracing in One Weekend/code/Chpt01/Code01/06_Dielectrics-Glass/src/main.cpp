

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
#include "material.h"


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
	
	
	//if (world.hit(r, 0, infinity, rec))
	if (world.hit(r, 0.001, infinity, rec))
	{
		/*
		//return 0.5 * (rec.normal + color(1, 1, 1));
		//point3 target = rec.p + rec.normal + random_in_unit_sphere();
		
		//point3 target = rec.p + rec.normal + vec.random_in_unit_sphere();
		//point3 target = rec.p + rec.normal + vec3::random_in_unit_sphere();

		//point3 target = rec.p + rec.normal + random_unit_vector();// non-unit length --> unit length vector
		point3 target = rec.p + random_in_hemisphere(rec.normal);// Chapter 8
		return 0.5 * ray_color(ray(rec.p, target - rec.p), world, depth - 1);// the factor(coefficient) 0.5 : our spheres only absorb half the energy on each bounce, so they are 50% reflectors.
		*/

		ray scattered;
		color attenuation;
		if (rec.mat_ptr->scatter(r, rec, attenuation, scattered))
			return attenuation * ray_color(scattered, world, depth - 1);

		return color(0, 0, 0);

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

	/*
	world.add(make_shared<sphere>(point3(0, 0, -1), 0.5));// small sphere on the top
	world.add(make_shared<sphere>(point3(0, -100.5, -1), 100));// big sphere at the bottom
	//world.add(make_shared<sphere>(point3(0, -100.6, -1), 100.6));// big sphere at the bottom
	*/

	auto material_ground = make_shared<lambertian>(color(0.8, 0.8, 0.0));// only red and green, no blue, that makes yellow!
	//auto material_ground = make_shared<metal>(color(0.8, 0.8, 0.0), 0.1);// only red and green, no blue, that makes yellow!
	// 
	auto material_center = make_shared<lambertian>(color(0.1, 0.2, 0.5));// mainly blue, that makes blue! diffuse!
	//auto material_center = make_shared<dielectric>(1.5);// transparent glass ball

	auto material_left = make_shared<dielectric>(1.5);// transparent glass ball
	//auto material_left = make_shared<metal>(color(0.8, 0.8, 0.8), 0.3);// more shiny!
	// 
	//auto material_right = make_shared<metal>(color(0.8, 0.6, 0.2), 1.0);//more shineless!
	auto material_right = make_shared<metal>(color(0.8, 0.6, 0.2), 0.0);//most shiny!


	world.add(make_shared<sphere>(point3(0, -100.5, -1), 100.0, material_ground));// Biggest ball as the ground!
	//world.add(make_shared<sphere>(point3(0, -100.5, -1), 100.0, material_left));// Biggest ball as the ground!
	world.add(make_shared<sphere>(point3(0, 0, -1), 0.5, material_center));// diffuse ball!
	world.add(make_shared<sphere>(point3(-1.0, 0, -1), 0.5, material_left));//shiny Metal ball!
	world.add(make_shared<sphere>(point3(-1.0, 0, -1), -0.4, material_left));//adding a inner hollow ball, with a negative radius, to make a bubble
	world.add(make_shared<sphere>(point3(1.0, 0, -1), 0.5, material_right));//Shineless Metal ball!


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