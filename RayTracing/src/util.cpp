/*
 * @Description:
 * @Author: НэПл
 * @Email: long452a@163.com
 * @Date: 2020-11-10
 */

#include "util.h"

namespace disc0ver {
	
	Scene* LoadScene(std::string s)
	{
		if (s == "twoSphere.ray") {
			std::cerr << "twoSphere" << std::endl;
			Scene* scene = twoSpheres();
			return scene;
		}
		else if (s == "twoPerlinSphere.ray") {
			std::cerr << "twoPerlinSphere" << std::endl;
			Scene* scene = twoPerlinSpheres();
			return scene;
		}
		return nullptr;
	}

	Scene* twoSpheres() {
		Scene* objects = new Scene();
		auto checker = std::make_shared<checkerTexture>(rgb(0.2, 0.3, 0.1), rgb(0.9, 0.9, 0.9));

		objects->add(std::make_shared<Sphere>(point(0, -10, 0), 10, std::make_shared<Lambertian>(checker)));
		objects->add(std::make_shared<Sphere>(point(0, 10, 0), 10, std::make_shared<Lambertian>(checker)));


		Camera* cam = new Camera();
		cam->setAspectRatio(16.0 / 9.0);
		cam->setEye(point(13, 2, 3));
		cam->setLookSimple(point(0, 0, 0), point(13, 2, 3));
		cam->setFOV(20);
		objects->setCamera(*cam);
		objects->getCamera().update();

		objects->sample = 100;

		rgb* background = new rgb(0.7, 0.8, 1.0);
		objects->setBackground(*background);
		return objects;
	}

	Scene* twoPerlinSpheres() {
		Scene* objects = new Scene();
		auto pertext = std::make_shared<noiseTexture>(4);

		objects->add(std::make_shared<Sphere>(point(0, -1000, 0), 1000, std::make_shared<Lambertian>(pertext)));
		objects->add(std::make_shared<Sphere>(point(0, 2, 0), 2, std::make_shared<Lambertian>(pertext)));


		Camera* cam = new Camera();
		cam->setAspectRatio(16.0 / 9.0);
		cam->setEye(point(13, 2, 3));
		cam->setLookSimple(point(0, 0, 0), point(13, 2, 3));
		cam->setFOV(20);
		objects->setCamera(*cam);
		objects->getCamera().update();

		objects->sample = 100;

		rgb* background = new rgb(0.7, 0.8, 1.0);
		objects->setBackground(*background);
		return objects;
	}
}