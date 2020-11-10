#include "Scene.h"

namespace disc0ver {
	bool Scene::hit(const Ray& r, double t_min, double t_max, hit_record& rec) const {
		hit_record tmp_rec;
		auto hit_anything = false;
		auto closest_so_fat = t_max;

		for (const auto& object : objects) {
			if (object->hit(r, t_min, closest_so_fat, tmp_rec)) {
				hit_anything = true;
				closest_so_fat = tmp_rec.t;
				rec = tmp_rec;
			}
		}
		return hit_anything;
	}

	bool Scene::bounding_box(AABB& output_box) const
	{
		if (objects.empty()) return false;

		AABB tmp_box;
		bool first_box = true;
		
		for (const auto& object : objects) {
			if (!object->bounding_box(tmp_box))
				return false;
			output_box = first_box ? tmp_box : surroundingBox(output_box, tmp_box);
			first_box = false;
		}
		
		return true;
	}
}