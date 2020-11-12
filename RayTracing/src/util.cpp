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
		Scene* scene = nullptr;
		if (s == "twoSphere.ray") {
			std::cerr << "twoSphere" << std::endl;
			scene = twoSpheres();
		}
		else if (s == "twoPerlinSphere.ray") {
			std::cerr << "twoPerlinSphere" << std::endl;
			scene = twoPerlinSpheres();
		}
		else if (s == "earth.ray") {
			std::cerr << "earth" << std::endl;
			scene = earth();
		}
		else if (s == "simpleLight.ray") {
			std::cerr << "simpleLight" << std::endl;
			scene = simpleLight();
		}
		else if (s == "randomScene.ray") {
			std::cerr << "randomScene" << std::endl;
			scene = randomScene();
		}
		else if (s == "cornellBox.ray") {
			std::cerr << "cornellBox" << std::endl;
			scene = cornellBox();
		}
		return scene;
	}

	Scene* randomScene() {
		Scene* objects = new Scene();
		auto checker = std::make_shared<checkerTexture>(rgb(0.2, 0.3, 0.1), rgb(0.9, 0.9, 0.9));

		objects->add(std::make_shared<Sphere>(point(0, -1000, 0), 1000, std::make_shared<Lambertian>(checker)));
		
		for (int a = -11; a < 11; a++) {
			for (int b = -11; b < 11; b++) {
				auto choose = random_double();
				point center(a + 0.9 * random_double(), 0.2, b + 0.9 * random_double());

				if ((center - vec3<TRANSFORM>(4, 0.2, 0)).length() > 0.9) {
					std::shared_ptr<Material> sphereMaterial;

					if (choose < 0.8) {
						auto albedo = rgb(random_double(), random_double(), random_double()) * rgb(random_double(), random_double(), random_double());
						sphereMaterial = std::make_shared<Lambertian>(albedo);
						objects->add(std::make_shared<Sphere>(center, 0.2, sphereMaterial));
					}
					else if (choose < 0.95) {
						auto albedo = rgb(random_double(0.5, 1), random_double(0.5, 1), random_double(0.5, 1)) * rgb(random_double(0.5, 1), random_double(0.5, 1), random_double(0.5, 1));
						auto fuzz = random_double(0, 0.5);
						sphereMaterial = std::make_shared<Metal>(albedo, fuzz);
						objects->add(std::make_shared<Sphere>(center, 0.2, sphereMaterial));
					}
					else {
						sphereMaterial = std::make_shared<Dielectric>(1.5);
						objects->add(std::make_shared<Sphere>(center, 0.2, sphereMaterial));
					}
				}
			}
		}

		auto material1 = std::make_shared<Dielectric>(1.5);
		objects->add(std::make_shared<Sphere>(point(0, 1, 0), 1.0, material1));

		auto material2 = std::make_shared<Lambertian>(rgb(0.4, 0.2, 0.1));
		objects->add(std::make_shared<Sphere>(point(-4, 1, 0), 1.0, material2));

		auto material3 = std::make_shared<Metal>(rgb(0.7, 0.6, 0.5), 0.0);
		objects->add(std::make_shared<Sphere>(point(4, 1, 0), 1.0, material3));

		Camera* cam = new Camera();
		cam->setAspectRatio(16.0 / 9.0);
		cam->setEye(point(13, 2, 3));
		cam->setLookSimple(point(0, 0, 0), point(13, 2, 3));
		cam->setFOV(20);
		objects->setCamera(*cam);
		objects->getCamera().update();

		objects->sample = 10;

		rgb* background = new rgb(0.7, 0.8, 1.0);
		objects->setBackground(*background);
		return objects;
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

	Scene* earth() {
		auto earthTexture = std::make_shared<ImageTexture>("images\\earthmap.jpg");
		auto earthSurface = std::make_shared<Lambertian>(earthTexture);
		auto globe = std::make_shared<Sphere>(point(0, 0, 0), 2, earthSurface);
		Scene* objects = new Scene(globe);


		Camera* cam = new Camera();
		cam->setAspectRatio(16.0 / 9.0);
		cam->setEye(point(0, 0, 12));
		cam->setLookSimple(point(0, 0, 0), point(0, 0, 12));
		cam->setFOV(20);
		objects->setCamera(*cam);
		objects->getCamera().update();

		objects->sample = 100;
			
		rgb* background = new rgb(0.7, 0.8, 1.0);
		objects->setBackground(*background);
		return objects;
	}

	Scene* simpleLight() {
		Scene* objects = new Scene();
		auto pertext = std::make_shared<noiseTexture>(4);
		objects->add(std::make_shared<Sphere>(point(0, -1000, 0), 1000, std::make_shared<Lambertian>(pertext)));
		objects->add(std::make_shared<Sphere>(point(0, 2, 0), 2, std::make_shared<Lambertian>(pertext)));

		auto difflight = std::make_shared<diffuseLight>(rgb(4, 4, 4));
		objects->add(std::make_shared<Sphere>(point(0, 7, 0), 2, difflight));
		objects->add(std::make_shared<xyRect>(3, 5, 1, 3, -2, difflight));

		Camera* cam = new Camera();
		cam->setAspectRatio(16.0 / 9.0);
		cam->setEye(point(26, 3, 6));
		cam->setLookSimple(point(0, 2, 0), point(26, 3, 6));
		cam->setFOV(20);
		objects->setCamera(*cam);
		objects->getCamera().update();

		objects->sample = 400;

		rgb* background = new rgb(0, 0, 0);
		objects->setBackground(*background);
		return objects;
	}

	Scene* cornellBox()
	{
		Scene* objects = new Scene();
		auto red = std::make_shared<Lambertian>(rgb(0.65, 0.05, 0.05));
		auto white = std::make_shared<Lambertian>(rgb(0.73, 0.73, 0.73));
		auto green = std::make_shared<Lambertian>(rgb(0.12, 0.45, 0.15));
		auto light = std::make_shared<diffuseLight>(rgb(3, 3, 3));

		objects->add(std::make_shared<yzRect>(0, 555, 0, 555, 555, green));
		objects->add(std::make_shared<yzRect>(0, 555, 0, 555, 0, red));
		objects->add(std::make_shared<xzRect>(113, 443, 127, 432, 554, light));
		//objects->add(std::make_shared<xzRect>(163, 393, 177, 382, 554, light));
		//objects->add(std::make_shared<xzRect>(213, 343, 227, 332, 554, light));
		objects->add(std::make_shared<xzRect>(0, 555, 0, 555, 555, white));
		objects->add(std::make_shared<xzRect>(0, 555, 0, 555, 0, white));
		objects->add(std::make_shared<xyRect>(0, 555, 0, 555, 555, white));

		Camera* cam = new Camera();
		cam->setAspectRatio(1.0);
		cam->setEye(point(278, 278, -800));
		cam->setLookSimple(point(278, 278, 0), point(278, 278, -800));
		cam->setFOV(40);
		objects->setCamera(*cam);
		objects->getCamera().update();

		objects->sample = 200;

		rgb* background = new rgb(0, 0, 0);
		objects->setBackground(*background);
		return objects;
	}
}