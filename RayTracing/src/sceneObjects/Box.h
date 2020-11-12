/*
 * @Description:
 * @Author: НэПл
 * @Email: long452a@163.com
 * @Date: 2020-11-12
 */

#ifndef BOX_H
#define BOX_H

#include "../scene/Hitable.h"
#include "../scene/Scene.h"
#include "rect.h"

namespace disc0ver {
	class Box : public Hitable{
	public:
		Box() = default;
		Box(const point& p0, const point& p1, std::shared_ptr<Material> ptr);

		virtual bool hit(const Ray& r, double t_min, double t_max, hit_record& rec) const override;
		virtual bool bounding_box(AABB& output_box) const override {
			output_box = AABB(boxMin, boxMax);
			return true;
		}
	public:
		point boxMax, boxMin;
		Scene sides;
	};
}

#endif // !BOX_H
