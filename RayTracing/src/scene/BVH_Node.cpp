/*
 * @Description:
 * @Author: 妄想
 * @Email: long452a@163.com
 * @Date: 2020-11-09
 */

#include "BVH_Node.h"

namespace disc0ver {
	BVH_Node::BVH_Node(std::vector<std::shared_ptr<Hitable>>& src_objects, size_t start, size_t end){
		auto objects = src_objects;
		int axis = random_int(0, 2);

		// 随机划分
		auto comparator = (axis == 0) ? boxCompareX :
			(axis == 1) ? boxCompareY : boxCompareZ;

		size_t object_span = end - start;
		if (object_span == 1) {
			left = right = objects[start];
		}
		else if (object_span == 2) {
			if (comparator(objects[start], objects[start + 1])) {
				left = objects[start];
				right = objects[start + 1];
			}
			else {
				left = objects[start + 1];
				right = objects[start];
			}
		}
		else {
			std::sort(objects.begin() + start, objects.begin() + end, comparator);

			auto mid = start + object_span / 2;
			left = std::make_shared<BVH_Node>(objects, start, mid);
			right = std::make_shared<BVH_Node>(objects, mid, end);
		}

		AABB box_left, box_right;

		if (!left->bounding_box(box_left) || !right->bounding_box(box_right))
			std::cerr << "No bounding box in bvh_node constructor.\n";
		
		box = surroundingBox(box_left, box_right);
	}

	bool BVH_Node::hit(const Ray& r, double t_min, double t_max, hit_record& rec) const
	{
		if (!box.hit(r, t_min, t_max))
			return false;

		bool hit_left = left->hit(r, t_min, t_max, rec);
		bool hit_right = right->hit(r, t_min, hit_left ? rec.t : t_max, rec);
		return hit_left || hit_right;
	}

	bool BVH_Node::bounding_box(AABB& output_box) const
	{
		output_box = box;
		return true;
	}

	inline bool boxCompare(const std::shared_ptr<Hitable> a, const std::shared_ptr<Hitable> b, int axis) {
		AABB box_a, box_b;

		if (!a->bounding_box(box_a) || !b->bounding_box(box_b))
			std::cerr << "No bounding box in bvh_node constructor.\n";

		return box_a.Min().e[axis] < box_b.Min().e[axis];
	}

	bool boxCompareX(const std::shared_ptr<Hitable> a, const std::shared_ptr<Hitable> b) { return boxCompare(a, b, 0); }

	bool boxCompareY(const std::shared_ptr<Hitable> a, const std::shared_ptr<Hitable> b) { return boxCompare(a, b, 1); }

	bool boxCompareZ(const std::shared_ptr<Hitable> a, const std::shared_ptr<Hitable> b) { return boxCompare(a, b, 2); }
}