/*
 * @Description: 材质相关类
 * @Author: 妄想
 * @Email: long452a@163.com
 * @Date: 2020-11-10
 */

#ifndef MATERIAL_H
#define MATERIAL_H

#include "Hitable.h"
#include "Texture.h"

namespace disc0ver {

	class Material {
	public:
		virtual rgb emitted(double u, double v, const point& p) const {
			return rgb(0, 0, 0);
		}

		// 产生散射射线
		virtual bool scatter(const Ray& r_in, const hit_record& rec, rgb& attenuation, Ray& scattered) const = 0;
	};

	// Lambertian 反射
	class Lambertian : public Material {
	public:
		Lambertian(const rgb& a) : albedo(std::make_shared<SolidColor>(a)){}
		Lambertian(std::shared_ptr<Texture> a) : albedo(a) {}

		virtual bool scatter(const Ray& r_in, const hit_record& rec, rgb& attenuation, Ray& scattered) const override{
			vec3<TRANSFORM> scatterDirection = rec.normal + randomUnitVector<TRANSFORM>();

			if (scatterDirection.near_zero())
				scatterDirection = rec.normal;

			scattered = Ray(rec.p, scatterDirection, r_in.t);
			attenuation = albedo->value(rec.u, rec.v, rec.p);
			return true;
		}

	private:
		std::shared_ptr<Texture> albedo;
	};

	// 电介质材质，即能够发生折射现象的材质
	class Dielectric : public Material {
	public:
		Dielectric(double indexOfRefraction) : ir(indexOfRefraction) {}

		virtual bool scatter(const Ray& r_in, const hit_record& rec, rgb& attenuation, Ray& scattered) const override {
			attenuation = rgb(1.0, 1.0, 1.0);
			double refractionRatio = rec.front_face ? (1.0 / ir) : ir;
			vec3<TRANSFORM> unitDirection = r_in.getDirection();
			unitDirection.normalize();
			double cos_theta = fmin(dot(-unitDirection, rec.normal), 1.0);
			double sin_theta = sqrt(1.0 - cos_theta * cos_theta);

			bool cannotRefract = refractionRatio * sin_theta > 1.0;
			vec3<TRANSFORM> direction;

			if (cannotRefract || reflectance(cos_theta, refractionRatio) > random_double()) {
				direction = reflect(unitDirection, rec.normal);
				scattered = Ray(rec.p, direction, Ray::RayType::REFLECTION);
			}
			else {
				direction = refract(unitDirection, rec.normal, refractionRatio);
				scattered = Ray(rec.p, direction, Ray::RayType::REFRACTION);
			}
			return true;
		}

	public:
		double ir;

	private:
		static double reflectance(double cosine, double eta_t) {
			// 使用Schlick近似值计算反射系数
			// R0 = ((eta_i - eta_t) / (eta_i + eta_t)) ^ 2;
			// R = R0 + (1 - R0) * (1 - cosine) ^ 5;
			auto r0 = (1 - eta_t) / (1 + eta_t);
			r0 *= r0;
			return r0 + (1 - r0) * std::pow(1 - cosine, 5);
		}
	};

	class diffuseLight : public Material {
	public:
		diffuseLight(std::shared_ptr<Texture> a) : emit(a){}
		diffuseLight(rgb c) : emit(std::make_shared<SolidColor>(c)){}

		virtual bool scatter(const Ray& r_in, const hit_record& rec, rgb& attenuation, Ray& scattered) const override {
			return false;
		}

		virtual rgb emitted(double u, double v, const point& p) const override {
			return emit->value(u, v, p);
		}
	private:
		std::shared_ptr<Texture> emit;
	};
}

#endif // !MATERIAL_H
