/*
 * @Description:
 * @Author: НэПл
 * @Email: long452a@163.com
 * @Date: 2020-11-07
 */

#ifndef RAY_H
#define RAY_H

#include "../vecmath/DGM.h"

namespace disc0ver {
	class Ray {
	public:
		enum class RayType { VISIBILITY, REFLECTION, REFRACTION, SHADOW };

		Ray() = default;
		~Ray(){}
		Ray(const point& origin, const vec3<TRANSFORM>& dirction, RayType t = RayType::VISIBILITY) : origin(origin), dir(dirction), t(t){}
		Ray(const Ray& other) : origin(other.origin), dir(other.dir), t(other.t){}
		
		point at(double t) const { return origin + dir * t; }
		point getOrigin() const { return origin; }
		point getDirection() const { return dir; }

		RayType getType() const { return t; }

	public:
		point origin;
		vec3<TRANSFORM> dir;
		RayType t;
	};
}

#endif // !RAY_H
