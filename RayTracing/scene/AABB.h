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
namespace disc0ver {

	class AABB {
	public:
		AABB();
		AABB(const point& a, const point& b) { minP = a; maxP = b; }

		point Min() const { return minP; }
		point Max() const { return maxP; }

		bool intersect(const Ray& r, double& tMin, double& tMax) const;


	public:
		point minP, maxP;
	};
}

#endif // !AABB_H
