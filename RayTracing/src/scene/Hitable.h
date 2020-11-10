/*
 * @Description:
 * @Author: НэПл
 * @Email: long452a@163.com
 * @Date: 2020-11-09
 */

#ifndef HITABLE_H
#define HITABLE_H

#include "AABB.h"

#include <memory>

namespace disc0ver {
	class Material;

	struct hit_record {
		point p;
		vec3<TRANSFORM> normal;
		std::shared_ptr<Material> mat_ptr;
		double t, u, v;
		bool front_face;

		inline void setFaceNormal(const Ray& r, const vec3<TRANSFORM> outward_normal) {
			front_face = dot(r.getDirection(), outward_normal) < 0;
			normal = front_face ? outward_normal : -outward_normal;
		}
	};

	class Hitable {
	public:
		virtual bool hit(const Ray& r, double t_min, double t_max, hit_record& rec) const = 0;
		virtual bool bounding_box(AABB& output_box) const = 0;
	};

}

#endif // !HITABLE_H
