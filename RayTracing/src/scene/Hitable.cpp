/*
 * @Description:
 * @Author: НэПл
 * @Email: long452a@163.com
 * @Date: 2020-11-09
 */

#include "Hitable.h"

namespace disc0ver {
	RotateY::RotateY(std::shared_ptr<Hitable> p, double angle) : ptr(p)
	{
		auto randians = angle * M_PI / 180.0;
		sinTheta = sin(randians);
		cosTheta = cos(randians);
		hasBox = ptr->bounding_box(bbox);

		point minn(INFINITY, INFINITY, INFINITY);
		point maxx(-INFINITY, -INFINITY, -INFINITY);

		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 2; j++) {
				for (int k = 0; k < 2; k++) {
					auto x = i * bbox.Max().x + (1 - i) * bbox.Min().x;
					auto y = j * bbox.Max().y + (1 - j) * bbox.Min().y;
					auto z = k * bbox.Max().z + (1 - k) * bbox.Min().z;

					auto newx = cosTheta * x + sinTheta * z;
					auto newz = -sinTheta * x + cosTheta * z;

					vec3<TRANSFORM> v(newx, y, newz);

					for (int c = 0; c < 3; c++) {
						minn[c] = fmin(minn[c], v[c]);
						maxx[c] = fmax(maxx[c], v[c]);
					}
				}
			}
		}

		bbox = AABB(minn, maxx);
	}

	bool RotateY::hit(const Ray& r, double t_min, double t_max, hit_record& rec) const
	{
		auto origin = r.getOrigin();
		auto dir = r.getDirection();

		origin.x = cosTheta * r.getOrigin().x - sinTheta * r.getOrigin().z;
		origin.z = sinTheta * r.getOrigin().x + cosTheta * r.getOrigin().z;

		dir.x = cosTheta * r.getDirection().x - sinTheta * r.getDirection().z;
		dir.z = sinTheta * r.getDirection().x + cosTheta * r.getDirection().z;

		Ray rotateRay(origin, dir, r.getType());

		if (!ptr->hit(rotateRay, t_min, t_max, rec))
			return false;

		auto p = rec.p;
		auto normal = rec.normal;

		p.x = cosTheta * rec.p.x + sinTheta * rec.p.z;
		p.z = -sinTheta * rec.p.x + cosTheta * rec.p.z;

		normal.x = cosTheta * rec.normal.x + sinTheta * rec.normal.z;
		normal.x = -sinTheta * rec.normal.x + cosTheta * rec.normal.z;

		rec.p = p;
		rec.setFaceNormal(rotateRay, normal);

		return true;
	}

	
	bool Translate::hit(const Ray& r, double t_min, double t_max, hit_record& rec) const
	{
		Ray movedRay(r.getOrigin() - offset, r.getDirection(), r.getType());
		if (!ptr->hit(movedRay, t_min, t_max, rec))
			return false;

		rec.p += offset;
		rec.setFaceNormal(movedRay, rec.normal);
		return true;
	}

	bool Translate::bounding_box(AABB& output_box) const
	{
		if (!ptr->bounding_box(output_box))
			return false;

		output_box = AABB(output_box.Min() + offset, output_box.Max() + offset);
		return true;
	}

}

