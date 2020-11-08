#pragma once
#ifndef RAYTRACER_H
#define RAYTRACER_H

#include "vecmath/DGM.h"

namespace disc0ver {
	class RayTracer
	{
	public:
		RayTracer() :depth(0), m_bBufferReady(false) {}
		rgb trace();

		void setReady(bool ready) { m_bBufferReady = ready; }
		bool isReady() { return m_bBufferReady; }

		int depth;
	private:

		bool m_bBufferReady;
	};

}


#endif // !RAYTRACER_H



