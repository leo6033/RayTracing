#include "Box.h"

namespace disc0ver {
	Box::Box(const point& p0, const point& p1, std::shared_ptr<Material> ptr)
	{
		boxMin = p0;
		boxMax = p1;

		sides.add(std::make_shared<xyRect>(p0.x, p1.x, p0.y, p1.y, p1.z, ptr));
		sides.add(std::make_shared<xyRect>(p0.x, p1.x, p0.y, p1.y, p0.z, ptr));

		sides.add(std::make_shared<xzRect>(p0.x, p1.x, p0.z, p1.z, p1.y, ptr));
		sides.add(std::make_shared<xzRect>(p0.x, p1.x, p0.z, p1.z, p0.y, ptr));

		sides.add(std::make_shared<yzRect>(p0.y, p1.y, p0.z, p1.z, p1.x, ptr));
		sides.add(std::make_shared<yzRect>(p0.y, p1.y, p0.z, p1.z, p0.x, ptr));
	}

	bool Box::hit(const Ray& r, double t_min, double t_max, hit_record& rec) const
	{
		return sides.hit(r, t_min, t_max, rec);
	}


}
