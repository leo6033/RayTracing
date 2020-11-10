#include "RayTracer.h"

namespace disc0ver {
	RayTracer::RayTracer() : world(0), buffer(0), bufferWidth(256), bufferHeight(256), m_bBufferReady(false) {
		depth = 0;
	}

	RayTracer::~RayTracer() {
		delete world;
		delete[] buffer;
	}

	rgb RayTracer::trace(double u, double v)
	{
		Ray r = world->getCamera().getRay(u, v);
		rgb ret = traceRay(r, depth);
		for (int i = 0; i < 3; i++) {
			if (ret[i] < 0)ret[i] = 0;
			if (ret[i] > 1)ret[i] = 1;
		}
		return ret;
	}
	
	rgb RayTracer::traceRay(const Ray& r, int depth)
	{
		hit_record rec;

		if (depth <= 0)
			return rgb(0, 0, 0);

		if (!world->hit(r, 0.001, infinity, rec))
			return world->getBackground();

		Ray scattered;
		rgb attenuation;
		rgb emitted = rec.mat_ptr->emitted(rec.u, rec.v, rec.p);

		if (!rec.mat_ptr->scatter(r, rec, attenuation, scattered))
			return emitted;

		return emitted + attenuation * traceRay(scattered, depth - 1);
		return rgb();
	}
	
	void RayTracer::getBuffer(unsigned char *& buf, int& w, int& h)
	{
		buf = buffer;
		w = bufferWidth;
		h = bufferHeight;
	}

	double RayTracer::aspectRatio()
	{
		return sceneLoaded() ? world->getCamera().getAspectRatio() : 1;
	}
	
	void RayTracer::traceSetup(int w, int h)
	{
		if (bufferWidth != w || bufferHeight != h) {
			bufferWidth = w;
			bufferHeight = h;

			bufferSize = bufferWidth * bufferWidth * 3;
			delete[] buffer;
			buffer = new unsigned char[bufferSize];
		}
		memset(buffer, 0, w * h * 3);
		m_bBufferReady = true;
	}
	
	void RayTracer::tracePixel(int i, int j)
	{
		rgb col = rgb(0, 0, 0);
		if (!sceneLoaded())
			return;
		for (int s = 0; s < world->sample; s++) {
			double x = double(i + random_double()) / double(bufferWidth);
			double y = double(j + random_double()) / double(bufferHeight);

			col += trace(x, y);
		}

		auto r = col.r, g = col.g, b = col.b;
		if (r != r)r = 0.0;
		if (g != g)g = 0.0;
		if (b != b)b = 0.0;

		col = rgb(r, g, b);

		auto scale = 1.0 / world->sample;

		unsigned char* pixel = buffer + (i + j * bufferWidth) * 3;

		for (int i = 0; i < 3; i++) {
			col[i] = sqrt(scale * col[i]);
			if (col[i] < 0)col[i] = 0;
			if (col[i] > 0.999)col[i] = 0.999;
			pixel[i] = (int)(256.0 * col[i]);
		}
	}
	
	bool RayTracer::loadScene(char* fn)
	{
		std::vector<std::string> res;
		std::stringstream input(fn);
		std::string tmp;

		while (std::getline(input, tmp, '/')) {
			res.push_back(tmp);
		}

		std::cerr << "file name " << res[res.size() - 1] << std::endl;

		world = LoadScene(res[res.size() - 1]);

		if (!sceneLoaded())
			return false;
		return true;
	}
}

