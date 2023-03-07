#pragma once

#ifndef CAMERA_H
#define CAMERA_H

//#include "../../common/rtweekend.h"
#include "rtweekend.h"

class camera {
	private:
		point3 origin;
		point3 lower_left_corner;
		vec3 horizontal;
		vec3 vertical;
		vec3 u, v, w;
		double lens_radius;// 镜片半（孔）径（半光圈孔径）
	public:
		camera(
			point3 lookfrom,
			point3 lookat,
			vec3 vup,
			double vfov, // vertical field-of-view in degrees
			double aspect_ratio,// 画幅宽高比
			double aperture,//光圈，与通常镜头标注的光圈数值大小相反
			double focus_dist// 完全清楚对焦距离，手动对焦焦平面位置
		) {
			//auto aspect_ratio = 16.0 / 9.0;
			auto theta = degrees_to_radians(vfov);
			auto h = tan(theta/2);
			auto viewport_height = 2.0 * h;
			auto viewport_width = aspect_ratio * viewport_height;
			//auto focal_length = 1.0;

			w = unit_vector(lookfrom - lookat);
			u = unit_vector(cross(vup, w));
			v = cross(w, u);

			
			//origin = point3(0, 0, 0);
			origin = lookfrom;
			//horizontal = vec3(viewport_width, 0, 0);
			//horizontal = viewport_width * u;
			horizontal = focus_dist * viewport_width * u;
			//vertical = vec3(0, viewport_height, 0);
			//vertical = viewport_height * v;
			vertical = focus_dist * viewport_height * v;
			//lower_left_corner = origin - horizontal / 2 - vertical / 2 - vec3(0, 0, focal_length);// 焦平面的左下角
			lower_left_corner = origin - horizontal / 2 - vertical / 2 - w;// 焦平面的左下角
			lower_left_corner = origin - horizontal / 2 - vertical / 2 - focus_dist * w;// 焦平面的左下角

			lens_radius = aperture / 2;
		}


		/*ray get_ray(double u, double v) const {	
			return ray(origin, lower_left_corner + u * horizontal + v * vertical - origin);
		}*/

		ray get_ray(double s, double t) const {

			vec3 rd = lens_radius * random_in_unit_disk();
			vec3 offset = u * rd.x() + v * rd.y();

			return ray(
				origin + offset, 
				lower_left_corner + s * horizontal + t * vertical - origin - offset
			);
		}

};






#endif


