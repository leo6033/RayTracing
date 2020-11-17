/*
 * @Description: Èý½ÇÃæÆ¬
 * @Author: ÍýÏë
 * @Email: long452a@163.com
 * @Date: 2020-11-16
 */

#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "../scene/Hitable.h"

namespace disc0ver {
	struct Vertex {
	public:
		Vertex(point _pos = point(0, 0, 0), vec3<TRANSFORM> _normal = vec3<TRANSFORM>(0, 0, 0), float _u = 0, float _v = 0) : pos(_pos), normal(_normal), u(_u), v(_v) {}
		float u, v;
		point pos;
		vec3<TRANSFORM> normal;
	};

	class Triangle : public Hitable {
	public:
		Triangle(Vertex a, Vertex b, Vertex c, std::shared_ptr<Material> ptr);

		virtual bool hit(const Ray& r, double t_min, double t_max, hit_record& rec) const override;

		virtual bool bounding_box(AABB& output_box) const override {
			output_box = box;
			return true;
		}

	public:
		Vertex A, B, C;
		std::shared_ptr<Material> mat_ptr;
		AABB box;
	};
}

#endif // !TRIANGLE_H
