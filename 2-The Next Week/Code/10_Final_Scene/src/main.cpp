

//#include <stdio.h>
//#include <stdlib.h>

//#include "../../common/rtweekend.h"
#include "vec3.h"
#include "rtweekend.h"
#include "color.h"
#include "hittable_list.h"
#include "ray.h"
#include "sphere.h"
#include "aarect.h"
#include "moving_sphere.h"
#include "camera.h"
#include "material.h"
#include "bvh.h"
#include "box.h"
#include "constant_medium.h"

#include <iostream>

#include "chrono"// 头文件chrono 自c++ 11起

using namespace std::chrono;// chrono的所有函数都存储在命名空间chrono中

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

		ray scattered;
		color attenuation;
		if (rec.mat_ptr->scatter(r, rec, attenuation, scattered))
			return attenuation * ray_color(scattered, world, depth - 1);

		return color(0, 0, 0);

	}

	vec3 unit_direction = unit_vector(r.direction());
	auto t = 0.5 * (unit_direction.y() + 1.0);// (-1, 1) --> (0, 1)
	return (1.0 - t) * color(1.0, 1.0, 1.0) + t * color(0.5, 0.7, 1.0);// 球形外部随着y值变化而为线性渐变色(蓝色 blue)
//	return (1.0 - t) * color(1.0, 1.0, 1.0) + t * color(1.0, 0.5, 0.0);// 球形外部随着y值变化而为线性渐变色(红棕色 red-brown)
//	return (1.0 - t) * color(1.0, 1.0, 1.0) + t * color(0.5, 1.0, 0.0);// 球形外部随着y值变化而为线性渐变色(绿色 green)

}




// adding lights
color ray_color(const ray& r, const color& background, const hittable& world, int depth)
{
    hit_record rec;
    vec3 vec;

    // If we've exceeded the ray bounce limit, no more light is gathered.
    if (depth <= 0)
        return color(0, 0, 0);// black!

    if (!world.hit(r, 0.001, infinity, rec))
        return background;

    ray scattered;
    color attenuation;
    color emitted = rec.mat_ptr->emitted(rec.u, rec.v, rec.p);

    if (!rec.mat_ptr->scatter(r, rec, attenuation, scattered))
        return emitted;

//    return attenuation * ray_color(scattered, world, depth - 1);
    return emitted + attenuation * ray_color(scattered, background, world, depth - 1);

}






hittable_list random_scene()
{
	hittable_list world;

//	auto ground_material = make_shared<lambertian>(color(0.5, 0.5, 0.5));// Biggest ball as the earth(ground)
//	world.add(make_shared<sphere>(point3(0, -1000, 0), 1000, ground_material));

// checkered ground
    auto checker = make_shared<checker_texture>(color(0.2, 0.3, 0.1), color(0.9, 0.9, 0.9));
    world.add(make_shared<sphere>(point3(0, -1000, 0), 1000, make_shared<lambertian>(checker)));

	for (int a = -11; a< 11; a++)
	{
		for (int b = -11; b < 11; b++)// 441 balls in total
		{
			auto choose_mat = random_double();
			//point3 center(a + 0.9 * random_double(), 0.2, b + 0.9 * random_double());
			point3 center(a + 0.8 * random_double(), 0.2, b + 0.8 * random_double());// 减少交叉重叠,出现嵌入的情况
			//point3 center(a + 0.6 * random_double(), 0.2, b + 0.6 * random_double());// 完全防止交叉重叠,出现嵌入的情况

			if ((center - point3(0, 0.2, 0)).length() > 0.9 && (center - point3(-4, 0.2, 0)).length() > 0.9 && (center - point3(4, 0.2, 0)).length() > 0.9)
			// 与三颗大球的位置（距离）做比较，防止交叉重叠,出现嵌入的情况
			{
				shared_ptr<material> sphere_material;

				//if (choose_mat < 0.8)// 此分布范围（区间）最广，也就是让大部分球的材质为diffuse
				if (choose_mat < 0.6)// 此分布范围（区间）最广，也就是让大部分球的材质为diffuse
				{
					// diffuse
					auto albedo = color::random();
					sphere_material = make_shared<lambertian>(albedo);
                    auto center2 = center + vec3(0, random_double(0, 0.5), 0);
                    world.add(make_shared<sphere>(center, 0.2, sphere_material));// still
//                    world.add(make_shared<moving_sphere>(center, center2, 0.0, 1.0, 0.2, sphere_material));// moving
				//} else if (choose_mat < 0.95)// 进一步减小分布概率，让较少的球的材质为metal;
				} else if (choose_mat < 0.85)// 进一步减小分布概率，让较少的球的材质为metal;
				{
					// metal
					auto albedo = color::random(0.5, 1);// 让金属球颜色亮一些
					auto fuzz = random_double(0, 0.5);// 绒毛；模糊
					sphere_material = make_shared<metal>(albedo, fuzz);
                    world.add(make_shared<sphere>(center, 0.2, sphere_material));
				} else {
					// glass
					sphere_material = make_shared<dielectric>(1.5);// 玻璃球占比最少
                    world.add(make_shared<sphere>(center, 0.2, sphere_material));
				}

//				world.add(make_shared<sphere>(center, 0.2, sphere_material));
			}


		}
	}

	auto material1 = make_shared<dielectric>(1.5);// glass
	world.add(make_shared<sphere>(point3(0, 1, 0), 1.0, material1));// 中间的大玻璃球

	auto material2 = make_shared<lambertian>(color(0.4, 0.2, 0.1));// 棕色
	world.add(make_shared<sphere>(point3(-4, 1, 0), 1.0, material2));

	auto material3 = make_shared<metal>(color(0.7, 0.6, 0.5), 0.0);// 纯镜面银色金属球， 无fuzz
	world.add(make_shared<sphere>(point3(4, 1, 0), 1.0, material3));
	
//	return world;
//    return hittable_list(make_shared<bvh_node>(world, 0.0, 1.0));// moving 运动模糊
    return hittable_list(make_shared<bvh_node>(world, 0.0, 0.0));// still 静止的
}

// Scene with two checkered spheres
hittable_list two_spheres() {
    hittable_list objects;

    auto checker = make_shared<checker_texture>(color(0.2, 0.3, 0.1), color(0.9, 0.9, 0.9));

    objects.add(make_shared<sphere>(point3(0, -10, 0), 10, make_shared<lambertian>(checker)));
    objects.add(make_shared<sphere>(point3(0, 10, 0), 10, make_shared<lambertian>(checker)));

    return objects;
}

hittable_list two_tiled_spheres() {
    hittable_list objects;

    auto tiledText = make_shared<tiled_random_texture2>();
    objects.add(make_shared<sphere>(point3(0, -1000, 0), 1000, make_shared<lambertian>(tiledText)));
    objects.add(make_shared<sphere>(point3(0, 2, 0), 2, make_shared<lambertian>(tiledText)));

    return objects;

}

hittable_list two_perlin_spheres() {
    hittable_list objects;

//    auto pertext = make_shared<noise_texture>();
    auto pertext = make_shared<noise_texture>(4);
    objects.add(make_shared<sphere>(point3(0, -1000, 0), 1000, make_shared<lambertian>(pertext)));
    objects.add(make_shared<sphere>(point3(0, 2, 0), 2, make_shared<lambertian>(pertext)));

    return objects;
}

hittable_list earth() {
//    auto earth_texture = make_shared<image_texture>("../../../../images/textures/earth/earthmap.jpg");
    auto earth_texture = make_shared<image_texture>("../../../../images/textures/earth/005.jpg");
    auto earth_surface = make_shared<lambertian>(earth_texture);
    auto globe = make_shared<sphere>(point3(0, 0, 0), 2, earth_surface);

    return hittable_list(globe);
}

hittable_list simple_light()
{
    hittable_list objects;

    auto pertex = make_shared<noise_texture>(4);
    objects.add(make_shared<sphere>(point3(0, -1000, 0), 1000, make_shared<lambertian>(pertex)));
    objects.add(make_shared<sphere>(point3(0, 2, 0), 2, make_shared<lambertian>(pertex)));

    /*
    shared_ptr<material> difflight = make_shared<diffuse_light>(color(4, 4, 4));
    objects.add(make_shared<xy_rect>(3, 5, 1, 3, -2, difflight));
//    auto diffLight_Sphere = make_shared<diffuse_light>(color(4, 4, 4));
    objects.add(make_shared<sphere>(point3(0, 7, 0), 2, difflight));
     */

    shared_ptr<material> difflight_Pink = make_shared<diffuse_light>(color(4, 0, 4));
    shared_ptr<material> difflight_Yellow = make_shared<diffuse_light>(color(4, 4, 0));
    objects.add(make_shared<xy_rect>(3, 5, 1, 3, -2, difflight_Pink));
    objects.add(make_shared<sphere>(point3(0, 7, 0), 2, difflight_Yellow));


    return objects;
}


hittable_list cornell_box() {
    hittable_list objects;

    auto red = make_shared<lambertian>(color(0.65, 0.05, 0.05));
    auto white = make_shared<lambertian>(color(0.73, 0.73, 0.73));
    auto green = make_shared<lambertian>(color(0.12, 0.45, 0.15));
    auto light = make_shared<diffuse_light>(color(15, 15, 15));

    // make a box
    objects.add(make_shared<yz_rect>(0 ,555, 0, 555, 555, green));// right face
    objects.add(make_shared<yz_rect>(0, 555, 0, 555, 0, red));// left face
    objects.add(make_shared<xz_rect>(213, 343, 227, 332, 554, light));// a little bit lower than the top face
    objects.add(make_shared<xz_rect>(0, 555, 0, 555, 0, white));// bottom face
    objects.add(make_shared<xz_rect>(0, 555, 0, 555, 555, white));// top face
    objects.add(make_shared<xy_rect>(0, 555, 0, 555, 555, white));// front face

    return objects;
}




hittable_list cornell_box_with_two_boxes() {
    hittable_list objects;

    auto red = make_shared<lambertian>(color(0.65, 0.05, 0.05));
    auto white = make_shared<lambertian>(color(0.73, 0.73, 0.73));
    auto green = make_shared<lambertian>(color(0.12, 0.45, 0.15));
    auto light = make_shared<diffuse_light>(color(15, 15, 15));

    // make a box
    objects.add(make_shared<yz_rect>(0 ,555, 0, 555, 555, green));// right face
    objects.add(make_shared<yz_rect>(0, 555, 0, 555, 0, red));// left face
    objects.add(make_shared<xz_rect>(213, 343, 227, 332, 554, light));// a little bit lower than the top face
    objects.add(make_shared<xz_rect>(0, 555, 0, 555, 0, white));// bottom face
    objects.add(make_shared<xz_rect>(0, 555, 0, 555, 555, white));// top face
    objects.add(make_shared<xy_rect>(0, 555, 0, 555, 555, white));// front face

    objects.add(make_shared<box>(point3(130, 0, 65), point3(295, 165, 230), white));// the shorter one
    objects.add(make_shared<box>(point3(265, 0, 295), point3(430, 330, 460), white));// the taller one

    return objects;
}

hittable_list cornell_box_with_two_Y_rotated_boxes() {
    hittable_list objects;

    auto red = make_shared<lambertian>(color(0.65, 0.05, 0.05));
    auto white = make_shared<lambertian>(color(0.73, 0.73, 0.73));
    auto green = make_shared<lambertian>(color(0.12, 0.45, 0.15));
    auto light = make_shared<diffuse_light>(color(15, 15, 15));

    // make a box
    objects.add(make_shared<yz_rect>(0 ,555, 0, 555, 555, green));// right face
    objects.add(make_shared<yz_rect>(0, 555, 0, 555, 0, red));// left face
    objects.add(make_shared<xz_rect>(213, 343, 227, 332, 554, light));// a little bit lower than the top face
    objects.add(make_shared<xz_rect>(0, 555, 0, 555, 0, white));// bottom face
    objects.add(make_shared<xz_rect>(0, 555, 0, 555, 555, white));// top face
    objects.add(make_shared<xy_rect>(0, 555, 0, 555, 555, white));// front face


// Two boxes
//    objects.add(make_shared<box>(point3(130, 0, 65), point3(295, 165, 230), white));// the shorter one
//    objects.add(make_shared<box>(point3(265, 0, 295), point3(430, 330, 460), white));// the taller one

// Two Y-rotated boxes
// the taller one
    shared_ptr<hittable> box1 = make_shared<box>(point3(0, 0, 0), point3(165,330, 165), white);
    box1 = make_shared<rotate_y>(box1, 15);// 沿y轴旋转15度（degrees）,先旋转再平移！
    box1 = make_shared<translate>(box1, vec3(265, 0, 295));
    objects.add(box1);

    // the shorter one
    shared_ptr<hittable> box2 = make_shared<box>(point3(0, 0, 0), point3(165,165, 165), white);
    box2 = make_shared<rotate_y>(box2, -18);// 沿y轴旋转15度（degrees）,先旋转再平移！
    box2 = make_shared<translate>(box2, vec3(130, 0, 65));
    objects.add(box2);

    return objects;
}



hittable_list cornell_smoke() {
    hittable_list objects;

    auto red = make_shared<lambertian>(color(0.65, 0.05, 0.05));
    auto white = make_shared<lambertian>(color(0.73, 0.73, 0.73));
    auto green = make_shared<lambertian>(color(0.12, 0.45, 0.15));
//    auto light = make_shared<diffuse_light>(color(15, 15, 15));
    auto light = make_shared<diffuse_light>(color(7, 7, 7));

    // make a box
    objects.add(make_shared<yz_rect>(0 ,555, 0, 555, 555, green));// right face
    objects.add(make_shared<yz_rect>(0, 555, 0, 555, 0, red));// left face
//    objects.add(make_shared<xz_rect>(213, 343, 227, 332, 554, light));// a little bit lower than the top face
    objects.add(make_shared<xz_rect>(113, 443, 127, 432, 554, light));// make the light bigger!
    objects.add(make_shared<xz_rect>(0, 555, 0, 555, 0, white));// bottom face
    objects.add(make_shared<xz_rect>(0, 555, 0, 555, 555, white));// top face
    objects.add(make_shared<xy_rect>(0, 555, 0, 555, 555, white));// front face



// Two Y-rotated boxes
// the taller one
    shared_ptr<hittable> box1 = make_shared<box>(point3(0, 0, 0), point3(165,330, 165), white);
    box1 = make_shared<rotate_y>(box1, 15);// 沿y轴旋转15度（degrees）,先旋转再平移！
    box1 = make_shared<translate>(box1, vec3(265, 0, 295));
//    objects.add(box1);

    // the shorter one
    shared_ptr<hittable> box2 = make_shared<box>(point3(0, 0, 0), point3(165,165, 165), white);
    box2 = make_shared<rotate_y>(box2, -18);// 沿y轴旋转15度（degrees）,先旋转再平移！
    box2 = make_shared<translate>(box2, vec3(130, 0, 65));
//    objects.add(box2);

//    objects.add(make_shared<constant_medium>(box1, 0.01, color(0, 0, 0)));// black, smoke
//    objects.add(make_shared<constant_medium>(box2, 0.01, color(1, 1, 1)));// white, frog

    objects.add(make_shared<constant_medium>(box1, 0.01, color(1, 0.6, 0)));// orange, smoke #FF9900
    objects.add(make_shared<constant_medium>(box2, 0.01, color(1, 0, 1)));// pink, frog #FF00FF

    return objects;
}

hittable_list final_scene() {
    hittable_list boxes1;// the ragged floor
    auto ground = make_shared<lambertian>(color(0.48, 0.83, 0.53));// green

    // 1. the ragged floor formed by 400 little boxes
    const int boxes_per_side = 20;
    for (int i = 0; i < boxes_per_side; ++i) {
        for (int j = 0; j < boxes_per_side; ++j) {
            auto w = 100.0;
            auto x0 = -1000.0 + i * w;
            auto z0 = -1000.0 + j * w;
//            auto y0 = 0.0;
            auto y0 = -50.0;
            auto x1 = x0 + w;
            auto y1 = random_double(1, 101);
            auto z1 = z0 + w;

            boxes1.add(make_shared<box>(point3(x0, y0, z0), point3(x1, y1 ,z1), ground));
        }
    }

    hittable_list objects;

    objects.add(make_shared<bvh_node>(boxes1, 0, 1));

    // 2. the light on the roof
    auto light = make_shared<diffuse_light>(color(7, 7, 7));
    objects.add(make_shared<xz_rect>(123, 423, 147, 412, 554, light));

    // 3. the brown moving ball on the top left
    auto center1 = point3(400, 400, 200);
    auto center2 = center1 + vec3(60, 0, 0);
    auto moving_sphere_material = make_shared<lambertian>(color(0.7, 0.3, 0.1));
    objects.add(make_shared<moving_sphere>(center1, center2, 0, 1, 50, moving_sphere_material));

    // 4. the tranparent glass ball in the middle bottom
    objects.add(make_shared<sphere>(point3(260, 150, 45), 50, make_shared<dielectric>(1.5)));

    // 5. the smaller grey metal ball on the right
    //objects.add(make_shared<sphere>(	point3(0, 150, 145), 50, make_shared<metal>(color(0.8, 0.8, 0.9), 1.0)));

    // 5. the smaller pink metal ball on the right
    objects.add(make_shared<sphere>(	point3(0, 150, 145), 50, make_shared<metal>(color(0.9, 0.0, 0.9), 0.9)));


    // 6. the blue snooker ball
    // part 1 , the outer varnish/natual clear lacquer(清漆) layer
    auto boundary = make_shared<sphere>(point3(360, 150, 145), 70, make_shared<dielectric>(1.5));
    objects.add(boundary);
    // part 2, the inner blue, frog material ball
//    objects.add(make_shared<constant_medium>(boundary, 0.2, color(0.2, 0.4, 0.9)));
// part 2, the inner orange, frog material ball
    objects.add(make_shared<constant_medium>(boundary, 0.01, color(0.9, 0.4, 0)));


    // 7. the earth ball
    auto emat = make_shared<lambertian>(make_shared<image_texture>("../../../../images/textures/earth/005.jpg"));
    objects.add(make_shared<sphere>(point3(400, 200, 400), 100, emat));

    // 8. the big grind arenaceous(磨砂的) grey metal ball in the center
//    auto pertext = make_shared<noise_texture>(2);
    auto pertext = make_shared<noise_texture>(0.1, color(0.6, 0, 0.9));
    objects.add(make_shared<sphere>(point3(220, 280, 350), 80, make_shared<lambertian>(pertext)));








    return objects;


}








int main()
{
	auto startTime = system_clock::now();

    // http://c.biancheng.net/view/1352.html
	unsigned seed;// Random generator seed
	double result;
	seed = time(0);// 从“time_t”转换到“unsigned int”，可能丢失数据
	srand(seed);

	
	
	// Image
	auto aspect_ratio = 16.0 / 9.0;
	//const auto aspect_ratio = 3.0 / 2.0;
//	int image_width = 400;
//    int image_width = 3840;
//	const int image_width = 1200;
	int image_width = 1920;
//	int image_height = static_cast<int>(image_width /aspect_ratio);
//	const int samples_per_pixel = 500;
//	const int samples_per_pixel = 200;
	int samples_per_pixel = 50;
	int max_depth = 50;

	auto R = cos(pi/4);
	// World(Objects)
	hittable_list world;

//	auto world = random_scene();



	
// Camera

	//point3 lookfrom(-2, 2, 1);
	//point3 lookfrom(3, 3, 2);
	point3 lookfrom(13, 2, 3);
	//point3 lookat(0, 0, -1);
	point3 lookat(0, 0, 0);
	vec3 vup(0, 1, 0);
    auto vfov = 40.0;
	//auto dist_to_focus = (lookfrom - lookat).length();// 5.1961524227066320
	auto dist_to_focus = 10.0;// 手动对焦焦平面位置
	//auto aperture = 2.0;
	auto aperture = 0.0;
//    int image_height = static_cast<int>(image_width /aspect_ratio);
    color background(0, 0, 0);


    switch (0) {
        case 1:
            world = random_scene();
            lookfrom = point3(13, 2, 3);
            lookat = point3(0, 0, 0);
            vfov = 20.0;
            aperture = 0.1;
            break;

//        default:
        case 2:
            world = two_spheres();
            lookfrom = point3(13, 2, 3);
            lookat = point3(0, 0, 0);
            vfov = 20.0;
            aperture = 0.0;
            break;

        //default:
        case 3:
            world = two_tiled_spheres();
            lookfrom = point3(13, 2, 3);
            lookat = point3(0, 0, 0);
            vfov = 20.0;
            break;

//        default:；
        case 4:
            world = two_perlin_spheres();
            lookfrom = point3(13, 2, 3);
            lookat = point3(0, 0, 0);
            vfov = 20.0;
            break;

//        default:
        case 5:
            world = earth();
            lookfrom = point3(13, 2, 3);
            lookat = point3(0, 0, 0);
            vfov = 20.0;
            break;

//        default:
        case 6:
            world = simple_light();
            samples_per_pixel = 400;
            background = color(0.0, 0.0, 0.0);
            lookfrom = point3(26, 3, 6);
            lookat = point3(0, 2, 0);
            vfov = 20.0;
            break;
//        default:
        case 7:
            world = cornell_box();
            // Changing aspect ratio and viewing parameters.
            aspect_ratio = 1.0;
            image_width = 2000;
            samples_per_pixel = 5000;
//            max_depth = 200;
            background = color(0, 0, 0);
            lookfrom = point3(278, 278, -1000);// on the -z axis
            lookat = point3(278, 278, 0);
            vfov = 40.0;
            break;
//        default:
        case 8:
            world = cornell_box_with_two_boxes();
            // Changing aspect ratio and viewing parameters.
            aspect_ratio = 1.0;
            image_width = 2000;
            samples_per_pixel = 500;
//            max_depth = 200;
            background = color(0, 0, 0);
            lookfrom = point3(278, 278, -1000);// on the -z axis
            lookat = point3(278, 278, 0);
            vfov = 40.0;
            break;
//        default:
        case 9:
            world = cornell_box_with_two_Y_rotated_boxes();
            // Changing aspect ratio and viewing parameters.
            aspect_ratio = 1.0;
            image_width = 2000;
            samples_per_pixel = 500;
//            max_depth = 200;
            background = color(0, 0, 0);
            lookfrom = point3(278, 278, -1000);// on the -z axis
            lookat = point3(278, 278, 0);
            vfov = 40.0;
            break;
//        default:
        case 10:
            world = cornell_smoke();
            // Changing aspect ratio and viewing parameters.
            aspect_ratio = 1.0;
            image_width = 2000;
            samples_per_pixel = 2000;
//            max_depth = 200;
            background = color(0, 0, 0);
            lookfrom = point3(278, 278, -900);// on the -z axis
            lookat = point3(278, 278, 0);
            vfov = 40.0;
            break;
        default:
        case 11:
            world = final_scene();
            // Changing aspect ratio and viewing parameters.
            aspect_ratio = 1.0;
            image_width = 1200;
            samples_per_pixel = 300;
//            max_depth = 200;
            background = color(0, 0, 0);
//            lookfrom = point3(278, 278, -900);// camera on the -z axis
            lookfrom = point3(478, 278, -600);// camera on the -z axis
            lookat = point3(278, 278, 0);
            vfov = 40.0;
            break;

    }


    int image_height = static_cast<int>(image_width / aspect_ratio);
//	camera cam(lookfrom, lookat, vup, 20, aspect_ratio, aperture, dist_to_focus);
	camera cam(lookfrom, lookat, vup, vfov, aspect_ratio, aperture, dist_to_focus, 0.0, 1.0);// moving 动态模糊
//	camera cam(lookfrom, lookat, vup, vfov, aspect_ratio, aperture, dist_to_focus, 0.0, 0.0);// still 静止不动

	// Render

	std::cout << "P3\n" << image_width << " " << image_height << "\n255\n";
	std::cerr << "image_width　==　" << image_width << "，　image_height　==　" << image_height << "\n";
	for (int j = image_height -1; j >= 0; --j)
	{
//		std::cerr << "\n\r---------------------------\nScanlines remaining : " << j << ' ------------------------------------------\n' << std::flush << '\n';
		std::cerr << "\n\r---------------------------\nScanlines remaining : " << j << ' ------------------------------------------\n' << std::flush;

			
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
//					pixel_color += ray_color(r, world, max_depth);
					pixel_color += ray_color(r, background, world, max_depth);
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

    auto finishTime = system_clock::now();

    auto duration = duration_cast<microseconds>(finishTime - startTime);

    auto costTime = double(duration.count()) / 1000000;

//    std::cout << "cost time : " << costTime << "s." << std::endl;
    std::cerr << "cost time : " << costTime << "s." << std::endl;

	std::cerr << "\nDone.\n";



	return 0;
}
