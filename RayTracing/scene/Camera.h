/*
 * @Description:
 * @Author: ÍýÏë
 * @Email: long452a@163.com
 * @Date: 2020-11-07
 */

#ifndef CAMERA_H
#define CAMERA_H

#include "../vecmath/DGM.h"
#include "../vecmath/mat.h"
#include "Ray.h"

namespace disc0ver {
	class Camera {
		Camera();
		Ray getRay(double x, double y);
		void setEye(const point& eye) { this->eye = eye; }
		void setLook(double r, double i, double j, double k);
		void setLook(const vec3<TRANSFORM>& viewDir, const vec3<TRANSFORM>& upDir);
		void setFOV(double);
		void setAspectRatio(double);
		bool setLookSimple(const vec3<TRANSFORM>& v, const vec3<TRANSFORM>& pos);

		double getAspectRatio() { return aspectRatio; }

		const point& getEye() const { return eye; }
		const vec3<TRANSFORM>& getLook() const { return look; }
		const vec3<TRANSFORM>& getU() const { return u; }
		const vec3<TRANSFORM>& getV() const { return v; }

	private:
		Mat3d m; // Ðý×ª¾ØÕó
		double normalizedHeight;
		double aspectRatio; // ÆÁÄ»¿í¸ß±È

		void update();

		point eye;
		vec3<TRANSFORM> u, v, look;
	};
}

#endif // !CAMERA_H
