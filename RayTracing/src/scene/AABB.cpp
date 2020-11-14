/*
 * @Description:
 * @Author: НэПл
 * @Email: long452a@163.com
 * @Date: 2020-11-07
 */

#include "AABB.h"

namespace disc0ver {
	bool AABB::hit(const Ray& r, double& tMin, double& tMax) const
	{
		for (int a = 0; a < 3; a++) {
			auto t0 = fmin((minP[a] - r.getOrigin()[a]) / r.getDirection()[a],
				(maxP[a] - r.getOrigin()[a]) / r.getDirection()[a]);
			auto t1 = fmax((minP[a] - r.getOrigin()[a]) / r.getDirection()[a],
				(maxP[a] - r.getOrigin()[a]) / r.getDirection()[a]);
			tMin = fmax(t0, tMin);
			tMax = fmin(t1, tMax);
			if (tMax <= tMin)
				return false;
		}
		return true;
	}

	double AABB::area()
	{
		auto a = (double)maxP.x - (double)minP.x;
		auto b = (double)maxP.y - (double)minP.y;
		auto c = (double)maxP.z - (double)minP.z;
		return 2.0f * (a * b + b * c + c * a);
	}

	int AABB::longest_axis()
	{
		auto a = maxP.x - minP.x;
		auto b = maxP.y - minP.y;
		auto c = maxP.z - minP.z;
		if (a > b && a > c)
			return 0;
		else if (b > c)
			return 1;
		else
			return 2;
	}

	AABB surroundingBox(AABB box0, AABB box1) {
		point _small(fmin(box0.Min().x, box1.Min().x),
					 fmin(box0.Min().y, box1.Min().y),
					 fmin(box0.Min().z, box1.Min().z));

		point _big(fmax(box0.Max().x, box1.Max().x),
				   fmax(box0.Max().y, box1.Max().y),
				   fmax(box0.Max().z, box1.Max().z));

		return AABB(_small, _big);
	}
}