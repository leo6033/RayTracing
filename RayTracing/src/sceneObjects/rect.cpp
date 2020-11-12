/*
 * @Description:
 * @Author: НэПл
 * @Email: long452a@163.com
 * @Date: 2020-11-11
 */

#include "rect.h"

namespace disc0ver {
	bool xyRect::hit(const Ray& r, double t_min, double t_max, hit_record& rec) const
	{
		auto t = (k - r.getOrigin().z) / r.getDirection().z;
		if (t<t_min || t>t_max)
			return false;

		auto x = r.getOrigin().x + t * r.getDirection().x;
		auto y = r.getOrigin().y + t * r.getDirection().y;
		if (x<x0 || x>x1 || y<y0 || y>y1)
			return false;

		rec.u = (x - x0) / (x1 - x0);
		rec.v = (y - y0) / (y1 - y0);
		rec.t = t;
		auto outwardNormal = vec3<TRANSFORM>(0, 0, 1);
		rec.setFaceNormal(r, outwardNormal);
		rec.mat_ptr = mp;
		rec.p = r.at(t);
		
		return true;
	}
	
	bool xzRect::hit(const Ray& r, double t_min, double t_max, hit_record& rec) const
	{
		auto t = (k - r.getOrigin().y) / r.getDirection().y;
		if (t<t_min || t>t_max)
			return false;

		auto x = r.getOrigin().x + t * r.getDirection().x;
		auto z = r.getOrigin().z + t * r.getDirection().z;
		if (x<x0 || x>x1 || z<z0 || z>z1)
			return false;

		rec.u = (x - x0) / (x1 - x0);
		rec.v = (z - z0) / (z1 - z0);
		rec.t = t;
		auto outwardNormal = vec3<TRANSFORM>(0, 1, 0);
		rec.setFaceNormal(r, outwardNormal);
		rec.mat_ptr = mp;
		rec.p = r.at(t);

		return true;
	}
	
	bool yzRect::hit(const Ray& r, double t_min, double t_max, hit_record& rec) const
	{
		auto t = (k - r.getOrigin().x) / r.getDirection().x;
		if (t<t_min || t>t_max)
			return false;

		auto y = r.getOrigin().y + t * r.getDirection().y;
		auto z = r.getOrigin().z + t * r.getDirection().z;
		if (y<y0 || y>y1 || z<z0 || z>z1)
			return false;

		rec.u = (y - y0) / (y1 - y0);
		rec.v = (z - z0) / (z1 - z0);
		rec.t = t;
		auto outwardNormal = vec3<TRANSFORM>(1, 0, 0);
		rec.setFaceNormal(r, outwardNormal);
		rec.mat_ptr = mp;
		rec.p = r.at(t);

		return true;
	}
}