/*
 * @Description:
 * @Author: 妄想
 * @Email: long452a@163.com
 * @Date: 2020-11-07
 */

#include "Camera.h"

namespace disc0ver {
	Camera::Camera() {
		aspectRatio = 1;
		normalizedHeight = 1;

		eye = point(0, 0, 0);
		u = vec3<TRANSFORM>(1, 0, 0);
		v = vec3<TRANSFORM>(0, 1, 0);
		look = vec3<TRANSFORM>(0, 0, -1);
	}

	/*
	* 从屏幕上一点发射射线
	*/
	Ray Camera::getRay(double x, double y) {
		x -= 0.5;
		y -= 0.5;
		vec3<TRANSFORM> dir = look + u * x + v * y;
		dir.normalize();
		return Ray(eye, dir, Ray::RayType::VISIBILITY);
	}

	bool Camera::setLookSimple(const vec3<TRANSFORM>& v, const vec3<TRANSFORM>& pos) {
		vec3<TRANSFORM> top = vec3<TRANSFORM>(0, 1, 0);
		vec3<TRANSFORM> out;
		vec3<TRANSFORM> upDir;
		vec3<TRANSFORM> viewDir;
		viewDir = v - pos;
		if (viewDir.length() == 0)
			return false;

		viewDir.normalize();
		if (viewDir.x == 0 && viewDir.z == 0) {
			setLook(viewDir, vec3<TRANSFORM>(1, 0, 0));
			return true;
		}
		else {
			out = cross(viewDir, top);
			out.normalize();
			upDir = cross(out, viewDir);
			upDir.normalize();
			setLook(viewDir, upDir);
			return true;
		}
	}

	void Camera::update() {
		Vec3d tmp = m * Vec3d(1, 0, 0) * normalizedHeight * aspectRatio;
		u = vec3<TRANSFORM>(tmp[0], tmp[1], tmp[2]);
		tmp = m * Vec3d(0, 1, 0) * normalizedHeight;
		v = vec3<TRANSFORM>(tmp[0], tmp[1], tmp[2]);
		tmp = m * Vec3d(0, 0, -1);
		look = vec3<TRANSFORM>(tmp[0], tmp[1], tmp[2]);
	}

	/*
	* 通过四元数设置相机角度，默认朝向 z 轴负半轴，y 轴正半轴向上
	* 通过乘上旋转矩阵来旋转相机
	*/
	void Camera::setLook(double r, double i, double j, double k) {
		m[0][0] = 1.0 - 2.0 * (i * i + j * j);
		m[0][1] = 2.0 * (r * i - j * k);
		m[0][2] = 2.0 * (j * r + i * k);

		m[1][0] = 2.0 * (r * i + j * k);
		m[1][1] = 1.0 - 2.0 * (j * j + r * r);
		m[1][2] = 2.0 * (i * j - r * k);

		m[2][0] = 2.0 * (j * r - i * k);
		m[2][1] = 2.0 * (i * j + r * k);
		m[2][2] = 1.0 - 2.0 * (i * i + r * r);

		update();
	}

	void Camera::setLook(const vec3<TRANSFORM>& viewDir, const vec3<TRANSFORM>& upDir) {
		vec3<TRANSFORM> z = -viewDir;
		const vec3<TRANSFORM>& y = upDir;
		vec3<TRANSFORM> x = cross(y, z);

		m = Mat3d(x[0], x[1], x[2], y[0], y[1], y[2], z[0], z[1], z[2]).transpose();

		update();
	}

	void Camera::setFOV(double fov) {
		fov /= (180.0 / M_PI);
		normalizedHeight = 2 * tan(fov / 2);
		update();
	}

	void Camera::setAspectRatio(double ar) {
		aspectRatio = ar;
		update();
	}
}