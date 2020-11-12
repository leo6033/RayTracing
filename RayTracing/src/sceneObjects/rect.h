/*
 * @Description:
 * @Author: НэПл
 * @Email: long452a@163.com
 * @Date: 2020-11-11
 */

#ifndef RECT_H
#define RECT_H

#include "../scene/Hitable.h"

namespace disc0ver {
	class xyRect : public Hitable {
	public:
		xyRect() = default;

		xyRect(double _x0, double _x1, double _y0, double _y1, double _k, std::shared_ptr<Material> mat) : x0(_x0), x1(_x1), y0(_y0), y1(_y1), k(_k), mp(mat) {}

		virtual bool hit(const Ray& r, double t_min, double t_max, hit_record& rec) const override;
		
		virtual bool bounding_box(AABB& output_box) const override {
			output_box = AABB(point(x0, y0, k - 0.0001), point(x1, y1, k + 0.0001));
			return true;
		}
	public:
		std::shared_ptr<Material> mp;
		double x0, x1, y0, y1, k;
	};

	class xzRect : public Hitable {
	public:
		xzRect() = default;

		xzRect(double _x0, double _x1, double _z0, double _z1, double _k, std::shared_ptr<Material> mat) : x0(_x0), x1(_x1), z0(_z0), z1(_z1), k(_k), mp(mat){}

		virtual bool hit(const Ray& r, double t_min, double t_max, hit_record& rec) const override;

		virtual bool bounding_box(AABB& output_box) const override {
			output_box = AABB(point(x0, k - 0.0001, z0), point(x1, k + 0.0001, z1));
			return true;
		}
	public:
		std::shared_ptr<Material> mp;
		double x0, x1, z0, z1, k;
	};

	class yzRect : public Hitable {
	public:
		yzRect() = default;

		yzRect(double _y0, double _y1, double _z0, double _z1, double _k, std::shared_ptr<Material> mat) : y0(_y0), y1(_y1), z0(_z0), z1(_z1), k(_k), mp(mat) {}

		virtual bool hit(const Ray& r, double t_min, double t_max, hit_record& rec) const override;

		virtual bool bounding_box(AABB& output_box) const override {
			output_box = AABB(point(k - 0.0001, y0, z0), point(k + 0.0001, y1, z1));
			return true;
		}
	public:
		std::shared_ptr<Material> mp;
		double y0, y1, z0, z1, k;
	};
}

#endif // !RECT_H
