

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
#include "pdf.h"

#include <iostream>

#include "chrono"// 头文件chrono 自c++ 11起

#include <ctype.h>// 调用atoi函数
// https://www.cnblogs.com/icmzn/articles/14097860.html

#include <bits/stdc++.h>

using namespace std;
using namespace std::chrono;// chrono的所有函数都存储在命名空间chrono中


const char* const prog_name = "Peter Shirley RT Renderer";
const char* const prog_version = "version 1.0 (20231103)";

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
//    vec3 vec;

    // If we've exceeded the ray bounce limit, no more light is gathered.
    if (depth <= 0)
        return color(0, 0, 0);// black!

    // If the ray hits nothing, return the background color.
    if (!world.hit(r, 0.001, infinity, rec))
        return background;

    ray scattered;
//    color attenuation;
//    color emitted = rec.mat_ptr->emitted(rec.u, rec.v, rec.p);//error: no matching function for call to ‘material::emitted(double&, double&, point3&)’
    color emitted = rec.mat_ptr->emitted(r, rec, rec.u, rec.v, rec.p);
    double pdf1;
    double pdf2; // == pdf1
    color albedo;

//    if (!rec.mat_ptr->scatter(r, rec, attenuation, scattered))
    if (!rec.mat_ptr->scatter(r, rec, albedo, scattered, pdf1))// scatter for the current time
        return emitted;

//    auto on_light = point3(random_double(213, 243), 554, random_double(227, 332));// y(height) is a certain value
//    auto to_light = on_light - rec.p;
//    auto distance_squared = to_light.length_squared();
//    to_light = unit_vector(to_light);
//
//    if (dot(to_light,rec.normal) < 0)// the light is toward the opposite direction of the normal
//        return emitted;
//
//    double light_area = (343-213)*(332-227);
//    auto light_cosine = fabs(to_light.y());// to_light was already normalized within 1
//    if (light_cosine < 0.000001) // theta is near (+/- pi/2)
//        return emitted;

    cosine_pdf p(rec.normal);
    scattered = ray(rec.p, p.generate(), r.time());
//    pdf1 = distance_squared / (light_cosine * light_area);
    pdf1 = p.value(scattered.direction());
//    scattered = ray(rec.p, to_light, r.time());


    pdf2 = rec.mat_ptr->scattering_pdf(r, rec, scattered);// != pdf1
//    return attenuation * ray_color(scattered, world, depth - 1);
//    return emitted + attenuation * ray_color(scattered, background, world, depth - 1);// scatter for the next time
    return emitted + albedo * pdf2
                            * ray_color(scattered, background, world, depth - 1) / pdf1;

}

//color ray_color(const ray& r, const color& background, const hittable& world, const shared_ptr<hittable>& lights, int depth)
//main.cpp:311:88: error: cannot bind non-const lvalue reference of type ‘std::shared_ptr<hittable>&’ to an rvalue of type ‘std::shared_ptr<hittable>’
//  311 |                                         pixel_color += ray_color(r, background, world, lights, max_depth);
// add const in ray_color() function to solve this issue!
//color ray_color(const ray& r, const color& background, const hittable& world, const shared_ptr<hittable>& lights, int depth)
//color ray_color(const ray& r, const color& background, const hittable& world, shared_ptr<hittable>& lights, int depth)
color ray_color(const ray& r, const color& background, const hittable& world, shared_ptr<hittable> lights, int depth)
{
    hit_record rec;
//    vec3 vec;

    // If we've exceeded the ray bounce limit, no more light is gathered.
    if (depth <= 0)
        return color(0, 0, 0);// black!

    // If the ray hits nothing, return the background color.
    if (!world.hit(r, 0.001, infinity, rec))
        return background;

    ray scattered;
//    color attenuation;
    scatter_record srec;
    color emitted = rec.mat_ptr->emitted(r, rec, rec.u, rec.v, rec.p);
    double pdf_val;
    double pdf2;

    if (!rec.mat_ptr->scatter(r, rec, srec))
        return emitted;

    if (srec.is_specular) {
        return srec.attenuation * ray_color(srec.specular_ray, background, world, lights, depth - 1);
    }


    auto light_ptr = make_shared<hittable_pdf>(lights, rec.p);

    mixture_pdf mixed_pdf(light_ptr, srec.pdf_ptr);

    scattered = ray(rec.p, mixed_pdf.generate(), r.time());
    pdf_val = mixed_pdf.value(scattered.direction());

//    if(!pdf_val)
//    {
//        std::cerr << "pdf_val == 0!\n";
//    }

    if(emitted.length() > 0)
    {
//        std::cerr << "emitted <= 0!\n";
//    }
//    else
//    {
        if(depth < 2) {
            std::cerr << "emitted == " << emitted << " .\n";
        }
    }

    pdf2 = rec.mat_ptr->scattering_pdf(r, rec, scattered);// != pdf1

    if(pdf_val > 0) {
        if(depth < 2)
        {
            std::cerr << "pdf_val == " << pdf_val << " .\n";
        }
        return emitted + srec.attenuation * pdf2
                         * ray_color(scattered, background, world, lights, depth - 1) / pdf_val;
    }
    else
    {
        if(depth < 2)
        {
//        std::cerr << "pdf_val == 0!\n";
            std::cerr << "Error ! pdf_val == " << pdf_val << " .\n";
        }
//        return emitted;
        return emitted + srec.attenuation * pdf2 * ray_color(scattered, background, world, lights, depth - 1);
    }

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
//    objects.add(make_shared<xz_rect>(213, 343, 227, 332, 554, light));// a little bit lower than the top face
    objects.add(make_shared<flip_face>(make_shared<xz_rect>(213, 343, 227, 332, 554, light)));// flip the front face of the light
    objects.add(make_shared<xz_rect>(0, 555, 0, 555, 0, white));// bottom face
    objects.add(make_shared<xz_rect>(0, 555, 0, 555, 555, white));// top face
    objects.add(make_shared<xy_rect>(0, 555, 0, 555, 555, white));// front face
//    objects.add(make_shared<sphere>(point3(190, 90, 190), 90, light));// added by me! there is not this item in the origin book on V3! but if without this light item,
    // the image will be weird and very dark!


// Two boxes
//    objects.add(make_shared<box>(point3(130, 0, 65), point3(295, 165, 230), white));// the shorter one
//    objects.add(make_shared<box>(point3(265, 0, 295), point3(430, 330, 460), white));// the taller one

    shared_ptr<material> aluminum = make_shared<metal>(color(0.8, 0.85, 0.88), 0.0);

// Two Y-rotated boxes
// the taller one
    shared_ptr<hittable> box1 = make_shared<box>(point3(0, 0, 0), point3(165,330, 165), white);
//    shared_ptr<hittable> box1 = make_shared<box>(point3(0, 0, 0), point3(165,330, 165), aluminum);
    box1 = make_shared<rotate_y>(box1, 15);// 沿y轴旋转15度（degrees）,先旋转再平移！
    box1 = make_shared<translate>(box1, vec3(265, 0, 295));
    objects.add(box1);

    // add a glass ball that surround the shorter box!
    auto glass = make_shared<dielectric>(1.5);
    objects.add(make_shared<sphere>(point3(190, 90, 190), 90, glass));

    // the shorter one
    shared_ptr<hittable> box2 = make_shared<box>(point3(0, 0, 0), point3(165,165, 165), white);
    box2 = make_shared<rotate_y>(box2, -18);// 沿y轴旋转15度（degrees）,先旋转再平移！
    box2 = make_shared<translate>(box2, vec3(130, 0, 65));
//    objects.add(box2);

    return objects;
}


// 退出函数
inline void usage(int exit_value = 0)
{
    std::cerr << prog_name << "  usage! exit_value == " << exit_value << endl;
    exit(exit_value);
}

int main(int argc, char *argv[])
//int main()
{

    auto startTime = system_clock::now();

    // http://c.biancheng.net/view/1352.html
    unsigned seed;// Random generator seed
    double result;
    seed = time(0);// 从“time_t”转换到“unsigned int” ,可能丢失数据
    srand(seed);



    // Image
    auto aspect_ratio = 1.0;

    int image_width = 800;
    int image_height = static_cast<int>(image_width /aspect_ratio);
//	const int samples_per_pixel = 500;
//	const int samples_per_pixel = 200;
    int samples_per_pixel = 500;
    int max_depth = 50;

    // World(Objects)
    hittable_list world = cornell_box();

    color background(0, 0, 0);

// Camera

    point3 lookfrom = point3(278, 278, -800);// on the -z axis
    point3 lookat = point3(278, 278, 0);
    vec3 vup(0, 1, 0);

    //auto dist_to_focus = (lookfrom - lookat).length();// 5.1961524227066320
    auto dist_to_focus = 10.0;// 手动对焦焦平面位置
    //auto aperture = 2.0;
    auto aperture = 0.0;
    auto vfov = 40.0;
    auto time0 = 0.0;
    auto time1 = 1.0;


    bool debug_on = false;
    bool ofile_on = false;// 正在处理输出文件
    bool limit_on = false;// 是否限制输入值的类型为数值类型

    string ofile_name;// 记录出现的输出文件名
    int limit = -1;// 限制值
    vector <string> file_names;// 记录文件名

//    unordered_map<string, int> control_param = {
//    map<string, int> control_param = {
    unordered_map<string, int> control_param = {
            {"-depth", 1},
            {"-spp", 2}
    };
// https://blog.csdn.net/u013620306/article/details/127526385
// https://blog.csdn.net/gaoqiandr/article/details/127233513



    cout << "argc : " << argc << endl;
    for (int i = 0; i < argc; ++i) {//读取argv中的每个选项
        // output the i+1 th parameter value, 输出第i+1个参量
        cout << "argv[" << i << "] : " << argv[i] << endl;

        char* pchar = argv[i];
        switch(pchar[0]) {//确定选项类型：-h,-d,-v,-l,-o;或者其他
            case '-':{
                cerr << "case \'-\' found ! " << endl;

                string argvStr = pchar;
                int caseKey = control_param[pchar];
                cout << "arg[" << i << "] is " << pchar << endl;

                switch (caseKey) {

//                    case '-depth':
                    case 1:// '-depth'
                    {
                        int depth = atoi(argv[i + 1]);
                        max_depth = depth ? depth : max_depth;
                        cout << "set max_depth to " << max_depth << endl;
                        break;
                    }
//                    case '-spp':
                    case 2:// '-spp'
                    {
                        int spp = atoi(argv[i + 1]);
                        samples_per_pixel = spp ? spp : samples_per_pixel;
                        cout << "set spp to " << samples_per_pixel << endl;
                        break;
                    }
                    default://
                    {
                        switch (pchar[1]) {
                            case 'd':
                                // 处理调试：
                                cout<<"-d found:debugging turned on!"<<endl;
                                debug_on = true;
                                break;
                            case 'v'://处理版本请求
                                cout<<"-v found:version info displayed!"<<endl;
                                cout<<prog_name<<":"<<prog_version<<endl;
                                return 0;
                            case 'h'://处理帮助
                                cout<<"-h found:help info!"<<endl;
                                usage(1);
//                        return 1;
                            case 'o'://处理输出文件
                                cout<<"-o found:output file!"<<endl;
                                ofile_name = argv[i + 1];
                                ofile_on = true;
                                break;
                            case 'l'://处理限制量
                                cout<<"-l found:resorce limit!"<<endl;
                                limit_on = true;
                                break;
                            default://无法识别的选项
                                cerr<<prog_name<<":error:unrecognition option -:"<<pchar<<endl;
                                usage(-1);
//                        return -1;
                        }
                        break;
                    }
                }

                break;
            }

            case '>':// 保留原输入： 控制台窗口中输入 > ，程序无法识别，但是ide中调试参数填入 > 就可以，why?
            // 品味人生：终端里>是bash处理, 终端里输入的时候加上引号 ： '>' 1.ppm !
            // ./12_Cleaning_Up_PDF_Management '>' 1122.ppm -spp 10 -depth 5
            {
                cerr << "case \'>\' found ! " << endl;
                ofile_name = argv[i + 1];
                ofile_on = true;
                break;
            }

            /*
            default:// //不以'-'开头 ,是文件名
                if (ofile_on) {//输出文件名
                    cout << "file name : " << pchar << endl;
                    ofile_name = pchar;
                    ofile_on = false;//复位
                }
                else if(limit_on) {// 如果没有正在输出文件 ,且限制了输入值类型
                    limit_on = false;//复位
                    limit = atoi(pchar);
                    if (limit < 0) {// 转换失败 ,说明输入类型错误
                        std::cerr << prog_name << ": error : negtive value for limit!" << endl;
                        usage(-2);
                    }
                }
                else{// 文件名
                    file_names.push_back(pchar);
                }
                break;
                */
        }
    }

    /*
    if (file_names.empty()) {
        std::cerr << prog_name << ": error : no file for processing!" << endl;
        usage(3);
    }
    else{
        cout << (file_names.size() == 1 ? "File" : "Files") <<
        " to be processed are the followed : " << endl;
        for (int i = 0; i < file_names.size(); ++i) {
            cout << file_names[i] << "\t" << endl;
        }
        if (limit != -1){
            cout << "user-specified limit:" << limit << endl;
        }
        if (!ofile_name.empty()) {
            cout << "user-specified ofile : " << ofile_name << endl;
        }
    }
    */

    if(ofile_name.empty())
    {
        cerr << "output file name missing!" << endl;
        usage(-3);
        return -3;
    }
    else
//    if (!ofile_name.empty())
    {
        cerr << "user-specified ofile : " << ofile_name << endl;
    }

//    std::ofstream outputFile(ofile_name);
//    std::ostream outStream;
    std::ofstream outputFile;
    outputFile.open(ofile_name);

//    if(!outputFile.is_open())
//    {
//        std::cerr << "Can not open the target output file!" << endl;
//        return -2;
//    }

    // 清空输出缓冲区:
    // https://www.cppblog.com/biao/archive/2008/04/12/46888.aspx
    fflush(stdout);
    std::cout.clear();
    std::cout.flush();

    // 将 std::cout 的输出重定向到文件
    std::streambuf *coutBuf = std::cout.rdbuf(); // 保存原始的 cout 缓冲区
    std::cout.rdbuf(outputFile.rdbuf());

    // 现在，任何东西写入 std::cout 都会写入文件
//    std::cout << "这是写入文件的内容" << std::endl;


	camera cam(lookfrom, lookat, vup, vfov, aspect_ratio, aperture, dist_to_focus, time0, time1);

    // World

//    auto world = cornell_box();

//    shared_ptr<hittable> lights = make_shared<xz_rect>(213, 343, 227, 332, 554, shared_ptr<material>());
    auto lights = make_shared<hittable_list>();
//    shared_ptr<hittable_list> lights = make_shared<hittable_list>();
    auto light1 = make_shared<xz_rect>(213, 343, 227, 332, 554, shared_ptr<material>());
    light1->setName("light1");
    lights->add(light1);
    auto light2 = make_shared<sphere>(point3(190, 90, 190), 90, shared_ptr<material>());
    light2->setName("light2");
    lights->add(light2);
    // because the value lights added is a rvalue, so the lights turned into a rvalue too!

	// Render



	std::cout << "P3\n" << image_width << " " << image_height << "\n255\n";
	std::cerr << "image_width == " << image_width << " , image_height == " << image_height << "\n";


	for (int j = image_height -1; j >= 0; --j)
	{
        std::cerr << "\n \r --------------------------- Scanlines remaining : " << j << " ------------------------------------ \n" << std::flush;

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
//					pixel_color += ray_color(r, background, world, max_depth);

//					pixel_color += ray_color(r, background, world, lights, max_depth);

//                    auto curLight = lights->getObjByName("light1");
//					pixel_color += ray_color(r, background, world, curLight, max_depth);

                    auto curLight = lights->getObjByName("light2");
					pixel_color += ray_color(r, background, world, curLight, max_depth);

                    //main.cpp:311:88: error: cannot bind non-const lvalue reference of type ‘std::shared_ptr<hittable>&’ to an rvalue of type ‘std::shared_ptr<hittable>’
                    //  311 |                                         pixel_color += ray_color(r, background, world, lights, max_depth);
                    // add const in ray_color() function to solve this issue!
				}

				//write_color(std::cout, pixel_color);
				write_color(std::cout, pixel_color, samples_per_pixel);
//                if(outputFile.is_open())
//                {
////                    write_color(outputFile, pixel_color, samples_per_pixel);
//                    write_color(std::cout, pixel_color, samples_per_pixel);
//                }


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

//    // 恢复原始的 cout 缓冲区
    std::cout.rdbuf(coutBuf);
//
//    // 关闭文件
    outputFile.close();

//    if(outputFile.is_open())
//    {
//        outputFile << std::cout;
//
//    }

    auto finishTime = system_clock::now();

    auto duration = duration_cast<microseconds>(finishTime - startTime);

    auto costTime = double(duration.count()) / 1000000;

//    std::cout << "cost time : " << costTime << "s." << std::endl;
    std::cerr << "cost time : " << costTime << "s." << std::endl;

	std::cerr << "\nDone.\n";



	return 0;
}

