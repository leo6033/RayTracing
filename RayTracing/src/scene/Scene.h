/*
 * @Description:
 * @Author: НэПл
 * @Email: long452a@163.com
 * @Date: 2020-11-09
 */

#ifndef SCENE_H
#define SCENE_H

#include "Hitable.h"
#include "Camera.h"

#include <memory>
#include <vector>

namespace disc0ver {
	class Scene : public Hitable{
	public:
		Scene() = default;
		Scene(std::shared_ptr<Hitable> object) { add(object); }

		void clear() { objects.clear(); }
		void add(std::shared_ptr<Hitable> object) { objects.push_back(object); }

		void setCamera(Camera camera) { this->camera = camera; }
		Camera getCamera() { return camera; }

		void setBackground(rgb background) { this->background = background; }
		rgb getBackground() { return background; }


		virtual bool hit(const Ray& r, double t_min, double t_max, hit_record& rec) const override;
		virtual bool bounding_box(AABB& output_box) const override;

		
	public:
		int sample;
		std::vector<std::shared_ptr<Hitable>> objects;
		Camera camera;
		rgb background;
	};

}

#endif // !SCENE_H
