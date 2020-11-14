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

	class testCamera {
    public:
        testCamera() : testCamera(point(0, 0, -1), point(0, 0, 0), vec3<TRANSFORM>(0, 1, 0), 40, 1, 0, 10) {}

        testCamera(
            point lookfrom,
            point lookat,
            vec3<TRANSFORM>   vup,
            double vfov, // vertical field-of-view in degrees
            double aspect_ratio,
            double aperture,
            double focus_dist,
            double _time0 = 0,
            double _time1 = 0
        ) {
            auto theta = vfov * M_PI / 180.0;
            auto h = tan(theta / 2);
            auto viewport_height = 2.0 * h;
            auto viewport_width = aspect_ratio * viewport_height;

            this->aspect_ratio = aspect_ratio;

            w = lookfrom - lookat;
            w.normalize();
            u = cross(vup, w);
            u.normalize();
            v = cross(w, u);

            origin = lookfrom;
            horizontal = focus_dist * viewport_width * u;
            vertical = focus_dist * viewport_height * v;
            lower_left_corner = origin - horizontal / 2 - vertical / 2 - focus_dist * w;

            lens_radius = aperture / 2;
            time0 = _time0;
            time1 = _time1;
        }

        Ray getRay(double s, double t) const {
            vec3<TRANSFORM> rd = lens_radius * randomInUnitDisk<TRANSFORM>();
            vec3<TRANSFORM> offset = u * rd.x + v * rd.y;
            return Ray(
                origin + offset,
                lower_left_corner + s * horizontal + t * vertical - origin - offset,
                Ray::RayType::VISIBILITY
            );
        }

        double aspect_ratio;
    private:
        point origin;
        point lower_left_corner;
        vec3<TRANSFORM> horizontal;
        vec3<TRANSFORM> vertical;
        vec3<TRANSFORM> u, v, w;
        double lens_radius;
        double time0, time1;
	};
}

#endif // !CAMERA_H
