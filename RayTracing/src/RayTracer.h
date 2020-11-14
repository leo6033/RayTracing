#pragma once
#ifndef RAYTRACER_H
#define RAYTRACER_H

#include "vecmath/DGM.h"
#include "scene/Ray.h"
#include "scene/Scene.h"
#include "util.h"

#include <string>
#include <sstream>
#include <thread>

namespace disc0ver {
	class RayTracer
	{
	public:
		RayTracer();
		~RayTracer();
		rgb trace(double u, double v);
		rgb traceRay(const Ray& r, int depth);

		void getBuffer(unsigned char *& buf, int& w, int& h);
		double aspectRatio();
		void traceSetup(int w, int h);
		void tracePixel(int i, int j);

		bool loadScene(char* fn);

		bool sceneLoaded() { return world != NULL; }
		void setReady(bool ready) { m_bBufferReady = ready; }
		bool isReady() { return m_bBufferReady; }
		Scene& getScene() { return *world; }

		int depth;
	private:
		const double infinity = std::numeric_limits<double>::infinity();
		unsigned char* buffer;
		int bufferWidth, bufferHeight;
		int bufferSize;
		bool m_bBufferReady;

		Scene* world;
	};

}


#endif // !RAYTRACER_H