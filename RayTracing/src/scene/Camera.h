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
#include "../vecmath/vec.h"
#include "Ray.h"

namespace disc0ver {
	class Camera {
	public:
		Camera();
		/*Camera(point lookfrom, point lookat, vec3<TRANSFORM> vup, double vfov, double aspectRatio, double aperture, double focus_dist);*/
		Ray getRay(double x, double y);
		void setEye(const point& eye) { this->eye = eye; }
		void setLook(double r, double i, double j, double k);
		void setLook(const vec3<TRANSFORM>& viewDir, const vec3<TRANSFORM>& upDir);
		void setFOV(double);
		void setAspectRatio(double);
		bool setLookSimple(const vec3<TRANSFORM>& v, const vec3<TRANSFORM>& pos);

		double getAspectRatio() { return aspectRatio; }

		const point& getEye() const { return eye; }
		const Vec3f& getEye() { return Vec3f(eye.x, eye.y, eye.z); }
		const vec3<TRANSFORM>& getLook() const { return look; }
		const Vec3f& getLook() { return Vec3f(look.x, look.y, look.z); }
		//const vec3<TRANSFORM>& getU() const { return u; }
		const Vec3f& getU() const { return Vec3f(u[1], u[2], u[3]); }
		//const vec3<TRANSFORM>& getV() const { return v; }
		const Vec3f& getV() const { return Vec3f(v[1], v[2], v[3]); }
		void update();
	private:
		Mat3d m; // Ðý×ª¾ØÕó
		double normalizedHeight;
		double aspectRatio; // ÆÁÄ»¿í¸ß±È

		point eye;
		vec3<TRANSFORM> u, v, look;
	};
}

#endif // !CAMERA_H
