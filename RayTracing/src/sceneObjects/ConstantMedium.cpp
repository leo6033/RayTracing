/*
 * @Description:
 * @Author: НэПл
 * @Email: long452a@163.com
 * @Date: 2020-11-13
 */

#include "ConstantMedium.h"

namespace disc0ver {
	bool ConstantMedium::hit(const Ray& r, double t_min, double t_max, hit_record& rec) const
	{
		constexpr double infinity = std::numeric_limits<double>::infinity();
		hit_record rec1, rec2;
		if (!boundary->hit(r, -infinity, infinity, rec1))
			return false;
		if (!boundary->hit(r, rec1.t + 0.0001, infinity, rec2))
			return false;

		if (rec1.t < t_min) rec1.t = t_min;
		if (rec2.t > t_max) rec2.t = t_max;

		if (rec1.t >= rec2.t)
			return false;

		if (rec1.t < 0) rec1.t = 0;

		const auto rayLength = r.getDirection().length();
		const auto distanceInsideBound = (rec2.t - rec1.t) * rayLength;
		const auto hitDistance = negInvDensity * log(random_double());

		if (hitDistance > distanceInsideBound)
			return false;

		rec.t = rec1.t + hitDistance / rayLength;
		rec.p = r.at(rec.t);
		rec.normal = vec3<TRANSFORM>(1, 0, 0);
		rec.front_face = true;
		rec.mat_ptr = mptr;

		return true;
	}
}