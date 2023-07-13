#pragma once

#ifndef MATERIAL_H
#define MATERIAL_H

//#include "rtweekend.h"
#include "texture.h"
#include "onb.h"
#include "pdf.h"
//struct hit_record;

class material
{
	public:
//		virtual color emitted(double u, double v, const point3& p) const {
//            return color(0, 0, 0);
//        }

        virtual color emitted(const ray& r_in, const hit_record& rec, double u, double v, const point3& p) const {
                return color(0, 0, 0);
        }


        virtual bool scatter(// Include both reflection and refraction
			const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered
		) const = 0;

        virtual bool scatter(const ray& r_in, const hit_record& rec, color& albedo, ray& scattered, double& pdf
        ) const {
            return false;
        }

        virtual double scattering_pdf(const ray& r_in, const hit_record& rec, const ray& scattered
        ) const {
            return 0;
        }




};


class lambertian : public material
{
	public:

//		color albedo;
		shared_ptr<texture> albedo;
//        double dir_length1;
//        double dir_length2;
//        double dir_length3;
//        double dir_length4;



//		lambertian(const color& a) : albedo(a){};
		lambertian(const color& a) : albedo(make_shared<solid_color>(a)) {}
		lambertian(shared_ptr<texture> a) : albedo(a) {}

		virtual bool scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered)
			const override {
			auto scatter_direction = rec.normal + random_unit_vector();

			// Catch degenerate scatter direction
			if (scatter_direction.near_zero())
				scatter_direction = rec.normal;
			
//			scattered = ray(rec.p, scatter_direction);
			scattered = ray(rec.p, scatter_direction, r_in.time());
//			attenuation = albedo;// 反照率
			attenuation = albedo->value(rec.u, rec.v, rec.p);// 根据反照率计算反射的衰减
			return true;
		}

        virtual bool scatter(const ray& r_in, const hit_record& rec, color& alb, ray& scattered, double& pdf
        ) const override {
            onb uvw;
            uvw.build_from_w(rec.normal);
//           auto direction = random_in_hemisphere((rec.normal));
            auto direction = uvw.local(random_cosine_direction());
            scattered = ray(rec.p, unit_vector(direction), r_in.time());
            alb = albedo->value(rec.u, rec.v, rec.p);
            pdf = dot(uvw.w(), scattered.direction()) / pi;

            return true;
        }

        double scattering_pdf(
                const ray& r_in, const hit_record& rec, const ray& scattered
                ) const {
            double dir_length4 = scattered.direction().length();// unnormalized, not 1
            auto cosine = dot(rec.normal, unit_vector((scattered.direction())));
            return cosine < 0 ? 0 : cosine / pi;
        }

};

class metal : public material
{
	public:
		color albedo;
		double fuzz;

		metal(const color& a) : albedo(a){};
		metal(const color& a, double f) : albedo(a), fuzz(f < 1 ? f : 1) {};

		virtual bool scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered)
			const override {
			vec3 reflected = reflect(unit_vector(r_in.direction()), rec.normal);
			//scattered = ray(rec.p, reflected);
			double reflectedLengthSq = reflected.length_squared();
//			scattered = ray(rec.p, reflected + fuzz * random_in_unit_sphere());
			scattered = ray(rec.p, reflected + fuzz * random_in_unit_sphere(), r_in.time());
			attenuation = albedo;
			return (dot(scattered.direction(), rec.normal) > 0);
		};



};

class dielectric : public material {
	public:
		double ir;// Index of Refraction 相对折射率（in/refracted）
        dielectric(double index_of_refraction) : ir(index_of_refraction) {};

		virtual bool scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered
		) const override {
			attenuation = color(1.0, 1.0, 1.0);
			double refraction_ratio = rec.front_face ? (1.0 / ir) : ir;

			vec3 unit_direction = unit_vector(r_in.direction());

			double cos_theta = fmin(dot(-unit_direction, rec.normal), 1.0);
			double sin_theta = sqrt(1.0 - cos_theta * cos_theta);

			bool cannot_refract = refraction_ratio * sin_theta > 1.0;
			vec3 direction;

			//if (cannot_refract)
			if (cannot_refract || reflectance(cos_theta, refraction_ratio) > random_double())// 增加反射的光线的比例, 随机挑选
				direction = reflect(unit_direction, rec.normal);
			else
			//vec3 refracted = refract(unit_direction, rec.normal, refraction_ratio);
				direction = refract(unit_direction, rec.normal, refraction_ratio);

			//scattered = ray(rec.p, refracted);
//			scattered = ray(rec.p, direction);
			scattered = ray(rec.p, direction, r_in.time());
			return true;

		}



	private:
		static double reflectance(double cosine, double ref_idx)
		{
			// Use Schlick's approximation for reflectance.
			auto r0 = (1 - ref_idx) / (1 + ref_idx);
			r0 = r0 * r0;
			return r0 + (1 - r0) * pow((1 - cosine), 5);
		}


};

    class diffuse_light : public material {
    public:
        diffuse_light(shared_ptr<texture> a) : emit(a) {}
        diffuse_light(color c) : emit(make_shared<solid_color>(c)) {}

        virtual bool scatter(
                const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered
        ) const override {
            return false;
        }

//        virtual color emitted(double u, double v, const point3& p) const override {
//            return emit->value(u, v, p);
//        }


        virtual color emitted(const ray& r_in, const hit_record& rec, double u, double v, const point3& p) const override {
            if (rec.front_face)
                return emit->value(u, v, p);
            else
                return color(0, 0, 0);
        }




    public:
        shared_ptr<texture> emit;
    };



#endif















