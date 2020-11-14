/*
 * @Description:
 * @Author: НэПл
 * @Email: long452a@163.com
 * @Date: 2020-11-13
 */

#ifndef CONSTANTMEDIUM_H
#define CONSTANTMEDIUM_H

#include "../scene/Hitable.h"
#include "../scene/Material.h"
#include "../scene/Texture.h"

namespace disc0ver {
	class ConstantMedium : public Hitable {
	public:
		ConstantMedium(std::shared_ptr<Hitable> b, double d, std::shared_ptr<Texture> m) : boundary(b), negInvDensity(-1 / d), mptr(std::make_shared<Isotropic>(m)) {}

		ConstantMedium(std::shared_ptr<Hitable> b, double d, rgb c) : boundary(b), negInvDensity(-1 / d), mptr(std::make_shared<Isotropic>(c)) {}

		virtual bool hit(const Ray& r, double t_min, double t_max, hit_record& rec) const override;

		virtual bool bounding_box(AABB& output_box) const override {
			return boundary->bounding_box(output_box);
		}
	public:
		std::shared_ptr<Hitable> boundary;
		std::shared_ptr<Material> mptr;
		double negInvDensity;
	};
}

#endif // !CONSTANTMEDIUM_H
