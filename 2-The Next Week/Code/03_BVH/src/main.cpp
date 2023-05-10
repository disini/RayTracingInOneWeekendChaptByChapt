

//#include <stdio.h>
//#include <stdlib.h>

//#include "../../common/rtweekend.h"
#include "vec3.h"
#include "rtweekend.h"
#include "color.h"
#include "hittable_list.h"
#include "ray.h"
#include "sphere.h"
#include "moving_sphere.h"
#include "camera.h"
#include "material.h"
#include "bvh.h"


#include <iostream>

#include "chrono"// ͷ�ļ�chrono ��c++ 11��

using namespace std::chrono;// chrono�����к������洢�������ռ�chrono��

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
	return (1.0 - t) * color(1.0, 1.0, 1.0) + t * color(0.5, 0.7, 1.0);// �����ⲿ����yֵ�仯��Ϊ���Խ���ɫ
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
	return (1.0 - t) * color(1.0, 1.0, 1.0) + t * color(0.5, 0.7, 1.0);// �����ⲿ����yֵ�仯��Ϊ���Խ���ɫ
	



}

hittable_list random_scene()
{
	hittable_list world;

	auto ground_material = make_shared<lambertian>(color(0.5, 0.5, 0.5));// Biggest ball as the earth(ground)
	world.add(make_shared<sphere>(point3(0, -1000, 0), 1000, ground_material));

	for (int a = -11; a< 11; a++)
	{
		for (int b = -11; b < 11; b++)// 441 balls in total
		{
			auto choose_mat = random_double();
			//point3 center(a + 0.9 * random_double(), 0.2, b + 0.9 * random_double());
			point3 center(a + 0.8 * random_double(), 0.2, b + 0.8 * random_double());// ���ٽ����ص�,����Ƕ������
			//point3 center(a + 0.6 * random_double(), 0.2, b + 0.6 * random_double());// ��ȫ��ֹ�����ص�,����Ƕ������

			if ((center - point3(0, 0.2, 0)).length() > 0.9 && (center - point3(-4, 0.2, 0)).length() > 0.9 && (center - point3(4, 0.2, 0)).length() > 0.9)
			// �����Ŵ����λ�ã����룩���Ƚϣ���ֹ�����ص�,����Ƕ������
			{
				shared_ptr<material> sphere_material;

				//if (choose_mat < 0.8)// �˷ֲ���Χ�����䣩��㣬Ҳ�����ô󲿷���Ĳ���Ϊdiffuse
				if (choose_mat < 0.6)// �˷ֲ���Χ�����䣩��㣬Ҳ�����ô󲿷���Ĳ���Ϊdiffuse
				{
					// diffuse
					auto albedo = color::random();
					sphere_material = make_shared<lambertian>(albedo);
                    auto center2 = center + vec3(0, random_double(0, 0.5), 0);
//                    world.add(make_shared<sphere>(center, 0.2, sphere_material));
                    world.add(make_shared<moving_sphere>(center, center2, 0.0, 1.0, 0.2, sphere_material));
				//} else if (choose_mat < 0.95)// ��һ����С�ֲ����ʣ��ý��ٵ���Ĳ���Ϊmetal;
				} else if (choose_mat < 0.85)// ��һ����С�ֲ����ʣ��ý��ٵ���Ĳ���Ϊmetal;
				{
					// metal
					auto albedo = color::random(0.5, 1);// �ý�������ɫ��һЩ
					auto fuzz = random_double(0, 0.5);// ��ë��ģ��
					sphere_material = make_shared<metal>(albedo, fuzz);
                    world.add(make_shared<sphere>(center, 0.2, sphere_material));
				} else {
					// glass
					sphere_material = make_shared<dielectric>(1.5);// ������ռ������
                    world.add(make_shared<sphere>(center, 0.2, sphere_material));
				}

//				world.add(make_shared<sphere>(center, 0.2, sphere_material));
			}


		}
	}

	auto material1 = make_shared<dielectric>(1.5);// glass
	world.add(make_shared<sphere>(point3(0, 1, 0), 1.0, material1));// �м�Ĵ�����

	auto material2 = make_shared<lambertian>(color(0.4, 0.2, 0.1));// ��ɫ
	world.add(make_shared<sphere>(point3(-4, 1, 0), 1.0, material2));

	auto material3 = make_shared<metal>(color(0.7, 0.6, 0.5), 0.0);// ��������ɫ������ ��fuzz
	world.add(make_shared<sphere>(point3(4, 1, 0), 1.0, material3));
	
//	return world;
    return hittable_list(make_shared<bvh_node>(world, 0.0, 1.0));
}


int main()
{
	auto startTime = system_clock::now();

    // http://c.biancheng.net/view/1352.html
	unsigned seed;// Random generator seed
	double result;
	seed = time(0);// �ӡ�time_t��ת������unsigned int�������ܶ�ʧ����
	srand(seed);

	
	
	// Image
	const auto aspect_ratio = 16.0 / 9.0;
	//const auto aspect_ratio = 3.0 / 2.0;
	//const int image_width = 400;
//	const int image_width = 3840;
	const int image_width = 1200;
	const int image_height = static_cast<int>(image_width /aspect_ratio);
//	const int samples_per_pixel = 500;
//	const int samples_per_pixel = 200;
	const int samples_per_pixel = 50;
	const int max_depth = 50;

	auto R = cos(pi/4);
	// World(Objects)
	//hittable_list world;

	auto world = random_scene();

	


	//point3 lookfrom(-2, 2, 1);
	//point3 lookfrom(3, 3, 2);
	point3 lookfrom(13, 2, 3);
	//point3 lookat(0, 0, -1);
	point3 lookat(0, 0, 0);
	vec3 vup(0, 1, 0);
	//auto dist_to_focus = (lookfrom - lookat).length();// 5.1961524227066320
	auto dist_to_focus = 10.0;// �ֶ��Խ���ƽ��λ��
	//auto aperture = 2.0;
	auto aperture = 0.1;

//	camera cam(lookfrom, lookat, vup, 20, aspect_ratio, aperture, dist_to_focus);
	camera cam(lookfrom, lookat, vup, 20, aspect_ratio, aperture, dist_to_focus, 0.0, 1.0);

	// Render

	std::cout << "P3\n" << image_width << " " << image_height << "\n255\n";
	for (int j = image_height -1; j >= 0; --j)
	{
		std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush << '\n';		
	
			
		for (int i = 0; i < image_width ;++i)
		{
			//if (i > 180)// �������У�columns������
			//{
			//	write_color(std::cout, color(0, 0, 0));
			//}
			//else
			//{
				color pixel_color(0, 0, 0);
				for (int s=0; s < samples_per_pixel;++s)
				{
					auto u = (i + random_double()) / (image_width - 1);// ������ز���				
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

		//if ( j <= image_height - 6)// �������У�rows������
		//{
		//	return 0;
		//}
	}

    auto finishTime = system_clock::now();

    auto duration = duration_cast<microseconds>(finishTime - startTime);

    auto costTime = double(duration.count()) / 1000000;

//    std::cout << "cost time : " << costTime << "s." << std::endl;
    std::cerr << "cost time : " << costTime << "s." << std::endl;

	std::cerr << "\nDone.\n";



	return 0;
}