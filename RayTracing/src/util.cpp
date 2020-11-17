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
		else if (s == "finalScene.ray") {
			std::cerr << "finalScene" << std::endl;
			scene = finalScene();
		}
		else if (s == "triangle1.ray") {
			std::cerr << "triangle1" << std::endl;
			scene = triangle1();
		}
		else if (s == "triangle2.ray") {
			std::cerr << "triangle2" << std::endl;
			scene = triangle2();
		}
		return scene;
	}

	Scene* triangle1() {
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

		Vertex v1 = Vertex({ 555, 0, 555 }, { 0,0,0 }, 0, 0);
		Vertex v2 = Vertex({ 555, 555, 555 }, { 0,0,0 }, 0, 1);
		Vertex v3 = Vertex({ 220,555,555 }, { 0,0,0 }, 220 / 550.0, 1);
		Vertex v4 = Vertex({ 0, 555, 555 }, { 0,0,0 }, 1, 1);
		Vertex v5 = Vertex({ 0, 0, 555 }, { 0,0,0 }, 1, 0);

		auto earthTexture = std::make_shared<ImageTexture>("images\\earthmap.jpg");
		auto earthSurface = std::make_shared<Lambertian>(earthTexture);

		objects->add(std::make_shared<Triangle>(v5, v3, v1, std::make_shared<Metal>(rgb(0.7, 0.6, 0.5), 0.0)));

		objects->add(std::make_shared<Triangle>(v3, v2, v1, earthSurface));
		//objects->add(std::make_shared<Triangle>(v5, v3, v1, earthSurface));
		objects->add(std::make_shared<Triangle>(v4, v3, v5, earthSurface));
		

		std::shared_ptr<Hitable>box2 = std::make_shared<Box>(point(0, 0, 0), point(165, 165, 165), white);
		box2 = std::make_shared<RotateY>(box2, -18);
		box2 = std::make_shared<Translate>(box2, vec3<TRANSFORM>(130, 0, 65));
		//objects->add(box2);

		//objects->add(std::make_shared<ConstantMedium>(box1, 0.01, rgb(0, 0, 0)));
		objects->add(std::make_shared<ConstantMedium>(box2, 0.01, rgb(1, 1, 1)));

		Camera* cam = new Camera();
		cam->setAspectRatio(1.0);
		cam->setEye(point(278, 278, -800));
		cam->setLookSimple(point(278, 278, 0), point(278, 278, -800));
		cam->setFOV(40);
		objects->setCamera(*cam);
		objects->getCamera().update();

		objects->sample = 3000;

		rgb* background = new rgb(0, 0, 0);
		objects->setBackground(*background);
		return objects;
	}

	Scene* triangle2() {
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

		Vertex v1 = Vertex({ 555, 0, 555 }, { 0,0,0 }, 0, 0);
		Vertex v2 = Vertex({ 555, 555, 555 }, { 0,0,0 }, 0, 1);
		Vertex v3 = Vertex({ 220,555,555 }, { 0,0,0 }, 220 / 550.0, 1);
		Vertex v4 = Vertex({ 0, 555, 555 }, { 0,0,0 }, 1, 1);
		Vertex v5 = Vertex({ 0, 0, 555 }, { 0,0,0 }, 1, 0);

		auto earthTexture = std::make_shared<ImageTexture>("images\\earthmap.jpg");
		auto earthSurface = std::make_shared<Lambertian>(earthTexture);

		//objects->add(std::make_shared<Triangle>(v5, v3, v1, std::make_shared<Metal>(rgb(0.7, 0.6, 0.5), 0.0)));

		objects->add(std::make_shared<Triangle>(v3, v2, v1, earthSurface));
		objects->add(std::make_shared<Triangle>(v5, v3, v1, earthSurface));
		objects->add(std::make_shared<Triangle>(v4, v3, v5, earthSurface));


		std::shared_ptr<Hitable>box2 = std::make_shared<Box>(point(0, 0, 0), point(165, 165, 165), white);
		box2 = std::make_shared<RotateY>(box2, -18);
		box2 = std::make_shared<Translate>(box2, vec3<TRANSFORM>(130, 0, 65));
		//objects->add(box2);

		//objects->add(std::make_shared<ConstantMedium>(box1, 0.01, rgb(0, 0, 0)));
		//objects->add(std::make_shared<ConstantMedium>(box2, 0.01, rgb(1, 1, 1)));

		Camera* cam = new Camera();
		cam->setAspectRatio(1.0);
		cam->setEye(point(278, 278, -800));
		cam->setLookSimple(point(278, 278, 0), point(278, 278, -800));
		cam->setFOV(40);
		objects->setCamera(*cam);
		objects->getCamera().update();

		objects->sample = 3000;

		rgb* background = new rgb(0, 0, 0);
		objects->setBackground(*background);
		return objects;
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
		//objects->setCamera(*cam);
		//objects->getCamera().update();

		//objects->sample = 10;

		rgb* background = new rgb(0.7, 0.8, 1.0);
		Scene* world = new Scene(std::make_shared<BVH_Node>(objects));
		world->setCamera(*cam);
		world->getCamera().update();
		world->sample = 10;
		world->setBackground(*background);
		//objects->setBackground(*background);
		return world;
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
		auto pertext = std::make_shared<noiseTexture>(3);
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

		std::shared_ptr<Hitable> box1 = std::make_shared<Box>(point(0, 0, 0), point(165, 330, 165), white);
		box1 = std::make_shared<RotateY>(box1, 15);
		box1 = std::make_shared<Translate>(box1, vec3<TRANSFORM>(265, 0, 295));
		objects->add(box1);

		std::shared_ptr<Hitable>box2 = std::make_shared<Box>(point(0, 0, 0), point(165, 165, 165), white);
		box2 = std::make_shared<RotateY>(box2, -18);
		box2 = std::make_shared<Translate>(box2, vec3<TRANSFORM>(130, 0, 65));
		objects->add(box2);

		//objects->add(std::make_shared<ConstantMedium>(box1, 0.01, rgb(0, 0, 0)));
		//objects->add(std::make_shared<ConstantMedium>(box2, 0.01, rgb(1, 1, 1)));

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

	Scene* finalScene() {
		Scene boxes1;
		auto ground = std::make_shared<Lambertian>(rgb(0.48, 0.83, 0.53));

		const int boxesPerSide = 20;
		for (int i = 0; i < boxesPerSide; i++) {
			for (int j = 0; j < boxesPerSide; j++) {
				auto w = 100.0;
				auto x0 = -1000.0 + i * w;
				auto z0 = -1000.0 + j * w;
				auto y0 = 0.0;
				auto x1 = x0 + w;
				auto y1 = random_double(1, 101);
				auto z1 = z0 + w;

				boxes1.add(std::make_shared<Box>(point(x0, y0, z0), point(x1, y1, z1), ground));
			}
		}

		Scene* objects = new Scene();
		objects->add(std::make_shared<BVH_Node>(&boxes1));

		auto light = std::make_shared<diffuseLight>(rgb(7, 7, 7));
		objects->add(std::make_shared<xzRect>(123, 423, 147, 412, 554, light));
		//objects->add(std::make_shared<xzRect>(73, 473, 97, 462, 500, light));

		//auto center1 = point(400, 400, 200);
		//auto center2 = center1 + vec3<TRANSFORM>(30, 0, 0);
		
		objects->add(std::make_shared<Sphere>(point(260, 150, 45), 50, std::make_shared<Dielectric>(1.5)));
		objects->add(std::make_shared<Sphere>(point(0, 150, 145), 50, std::make_shared<Metal>(rgb(0.8, 0.8, 0.9), 1.0)));

		auto boundary = std::make_shared<Sphere>(point(360, 150, 145), 70, std::make_shared<Dielectric>(1.5));
		objects->add(boundary);
		objects->add(std::make_shared<ConstantMedium>(boundary, 0.2, rgb(0.2, 0.4, 0.9)));
		boundary = std::make_shared<Sphere>(point(0, 0, 0), 5000, std::make_shared < Dielectric>(1.5));
		objects->add(std::make_shared<ConstantMedium>(boundary, .0001, rgb(1, 1, 1)));

		auto emat = std::make_shared<Lambertian>(std::make_shared<ImageTexture>("images\\earthmap.jpg"));
		objects->add(std::make_shared<Sphere>(point(400, 200, 400), 100, emat));
		auto pertext = std::make_shared<noiseTexture>(0.1);
		objects->add(std::make_shared<Sphere>(point(220, 280, 300), 80, std::make_shared < Lambertian>(pertext)));

		Scene boxes2;
		auto white = std::make_shared<Lambertian>(rgb(0.73, 0.73, 0.73));
		int ns = 1000;
		for (int j = 0; j < ns; j++) {
			boxes2.add(std::make_shared<Sphere>(point(random_double(0, 165), random_double(0, 165), random_double(0, 165)), 10, white));
		}
		objects->add(std::make_shared<Translate>(
			std::make_shared<RotateY>(
				std::make_shared<BVH_Node>(&boxes2), 15
				),
			vec3<TRANSFORM>(-100, 270, 395)
			)
		);

		Camera* cam = new Camera();
		cam->setAspectRatio(1);
		cam->setEye(point(478, 278, -600));
		cam->setLookSimple(point(278, 278, 0), point(478, 278, -600));
		cam->setFOV(40);
		objects->setCamera(*cam);
		objects->getCamera().update();

		objects->sample = 10000;

		rgb* background = new rgb(0, 0, 0);
		//rgb* background = new rgb(0.7, 0.8, 1.0);
		objects->setBackground(*background);
		return objects;
	}
}