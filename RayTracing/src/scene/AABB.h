/*
 * @Description:
 * @Author: НэПл
 * @Email: long452a@163.com
 * @Date: 2020-11-07
 */

#ifndef AABB_H
#define AABB_H

#include "../vecmath/DGM.h"
#include "Ray.h"
#include <algorithm>

namespace disc0ver {

	class AABB {
	public:
		AABB() = default;
		AABB(const point& a, const point& b) { minP = a; maxP = b; }

		point Min() const { return minP; }
		point Max() const { return maxP; }

		bool hit(const Ray& r, double& tMin, double& tMax) const;
		double area();
		int longest_axis();

	public:
		point minP, maxP;
	};

	AABB surroundingBox(AABB box0, AABB box1); 
}

#endif // !AABB_H
