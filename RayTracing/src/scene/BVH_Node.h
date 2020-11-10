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
		BVH_Node() = default;
		BVH_Node(const Scene* scene) : BVH_Node() {};
		BVH_Node(const std::vector<std::shared_ptr<Hitable>>& src_objects, size_t start, size_t end);

		virtual bool hit(const Ray& r, double t_min, double t_max, hit_record& rec) const override;
		virtual bool bounding_box(AABB& output_box) const override;

	public:
		std::shared_ptr<Hitable> left;
		std::shared_ptr<Hitable> right;
		AABB box;
	};

	inline bool boxCompare(const std::shared_ptr<Hitable> a, const std::shared_ptr<Hitable> b, int axis) {
		AABB box_a, box_b;
		
		if(!a->bounding_box(box_a) || !b->bounding_box(box_b))
			std::cerr << "No bounding box in bvh_node constructor.\n";

		return box_a.Min().e[axis] < box_b.Min().e[axis];
	}

	bool boxCompareX(const std::shared_ptr<Hitable> a, const std::shared_ptr<Hitable> b) { return boxCompare(a, b, 0); }

	bool boxCompareY(const std::shared_ptr<Hitable> a, const std::shared_ptr<Hitable> b) { return boxCompare(a, b, 1); }

	bool boxCompareZ(const std::shared_ptr<Hitable> a, const std::shared_ptr<Hitable> b) { return boxCompare(a, b, 2); }

}

#endif // !BVHNODE_H
