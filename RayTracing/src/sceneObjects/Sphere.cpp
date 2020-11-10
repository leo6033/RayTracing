/*
 * @Description:
 * @Author: НэПл
 * @Email: long452a@163.com
 * @Date: 2020-11-10
 */

#include "Sphere.h"

namespace disc0ver {
	bool Sphere::hit(const Ray& r, double t_min, double t_max, hit_record& rec) const
	{
		//YOUR CODE HERE
		vec3<TRANSFORM> oc = r.getOrigin() - center;
		double a = r.getDirection().squared_length();
		double b = dot(oc, r.getDirection());
		double c = oc.squared_length() - radius * radius;
		
		//std::cerr << a << " " << b << " " << c << std::endl;
		double discriminant = b * b - a * c;
		if (discriminant < 0) 
			return false;
		auto sqrtd = sqrt(discriminant);

		auto root = (-b - sqrtd) / a;
		if (root < t_min || t_max < root) {
			root = (-b + sqrtd) / a;
			if (root < t_min || t_max < root)
				return false;
		}

		rec.t = root;
		rec.p = r.at(rec.t);
		vec3<TRANSFORM> outwardNormal = (rec.p - center) / radius;
		rec.setFaceNormal(r, outwardNormal);
		getSphereUV(outwardNormal, rec.u, rec.v);
		rec.mat_ptr = mat_ptr;
		return true;
	}
	
	bool Sphere::bounding_box(AABB& output_box) const
	{
		output_box = AABB(center - point(radius, radius, radius), center + point(radius, radius, radius));
		return true;
	}
}