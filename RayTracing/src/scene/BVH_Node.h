/*
 * @Description:
 * @Author: НэПл
 * @Email: long452a@163.com
 * @Date: 2020-11-09
 */

#ifndef BVHNODE_H
#define BVHNODE_H

#include "Hitable.h"
#include "Scene.h"

#include <algorithm>
#include <memory>

namespace disc0ver {
	class BVH_Node : public Hitable{
	public:
		BVH_Node();
		BVH_Node(Scene* scene) : BVH_Node(scene->objects, 0, scene->objects.size()) {};
		BVH_Node(std::vector<std::shared_ptr<Hitable>>& src_objects, size_t start, size_t end);

		virtual bool hit(const Ray& r, double t_min, double t_max, hit_record& rec) const override;
		virtual bool bounding_box(AABB& output_box) const override;

		void setCamera(Camera camera) { this->camera = camera; }
		Camera getCamera() { return camera; }

		void setBackground(rgb background) { this->background = background; }
		rgb getBackground() { return background; }
		
		int sample;
	public:
		std::shared_ptr<Hitable> left;
		std::shared_ptr<Hitable> right;
		AABB box;
		Camera camera;
		rgb background;
	};

	inline bool boxCompare(const std::shared_ptr<Hitable> a, const std::shared_ptr<Hitable> b, int axis);

	bool boxCompareX(const std::shared_ptr<Hitable> a, const std::shared_ptr<Hitable> b);

	bool boxCompareY(const std::shared_ptr<Hitable> a, const std::shared_ptr<Hitable> b);

	bool boxCompareZ(const std::shared_ptr<Hitable> a, const std::shared_ptr<Hitable> b);

}

#endif // !BVHNODE_H
