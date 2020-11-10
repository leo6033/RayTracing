/*
 * @Description:
 * @Author: НэПл
 * @Email: long452a@163.com
 * @Date: 2020-11-10
 */

#ifndef SPHERE_H
#define SPHERE_H

#include "../scene/Hitable.h"

namespace disc0ver {
	class Sphere : public Hitable{
	public:
		Sphere() = default;
		Sphere(point cen, double r, std::shared_ptr<Material> m) : center(cen), radius(r), mat_ptr(m){}

		virtual bool hit(const Ray& r, double t_min, double t_max, hit_record& rec) const override;

		virtual bool bounding_box(AABB& output_box) const override;
	public:
		point center;
		double radius;
		std::shared_ptr<Material> mat_ptr;

	private:
		static void getSphereUV(const point& p, double& u, double& v) {

		}
	};
}

#endif // !SPHERE_H
