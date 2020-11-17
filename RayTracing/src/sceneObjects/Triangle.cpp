/*
 * @Description:
 * @Author: НэПл
 * @Email: long452a@163.com
 * @Date: 2020-11-16
 */

#include "Triangle.h"

namespace disc0ver {
	Triangle::Triangle(Vertex a, Vertex b, Vertex c, std::shared_ptr<Material> ptr): A(a), B(b), C(c), mat_ptr(ptr){
		vec3<TRANSFORM> minP = vec3<TRANSFORM>(
			min(min(A.pos.x, B.pos.x), C.pos.x),
			min(min(A.pos.y, B.pos.y), C.pos.y),
			min(min(A.pos.z, B.pos.z), C.pos.z)
			);

		vec3<TRANSFORM> maxP = vec3<TRANSFORM>(
			max(max(A.pos.x, B.pos.x), C.pos.x),
			max(max(A.pos.y, B.pos.y), C.pos.y),
			max(max(A.pos.z, B.pos.z), C.pos.z)
			);

		for (int i = 0; i < 3; i++) {
			if (minP[i] == maxP[i]) {
				minP[i] -= 0.001f;
				maxP[i] += 0.001f;
			}
		}
		
		box = AABB(minP, maxP);
	}

	bool Triangle::hit(const Ray& r, double t_min, double t_max, hit_record& rec) const
	{
		vec3<TRANSFORM> n = cross((B.pos - A.pos), (C.pos - A.pos));
		if (n.length() != 0)
			n.normalize();
		else 
			return false;

		vec3<TRANSFORM> pos = r.getOrigin();
		vec3<TRANSFORM> dir = r.getDirection();

		if (fabs(dot(n, dir)) < 0.00001)
			return false;
		
		double d = dot(n, A.pos);
		double t = (d - dot(n, pos)) / dot(n, dir);

		vec3<TRANSFORM> Q = r.at(t);
		if (dot(cross(B.pos - A.pos, Q - A.pos), n) < 0 || dot(cross(C.pos - B.pos, Q - B.pos), n) < 0 || dot(cross(A.pos - C.pos, Q - C.pos), n) < 0)
			return false;

		if (t < t_min || t > t_max)
			return false;

		double alpha = fabs(dot(cross(C.pos - B.pos, Q - B.pos), n)) / fabs(dot(cross(B.pos - A.pos, C.pos - A.pos), n));
		double beta = fabs(dot(cross(A.pos - C.pos, Q - C.pos), n)) / fabs(dot(cross(B.pos - A.pos, C.pos - A.pos), n));
		double gamma = fabs(dot(cross(A.pos - B.pos, Q - B.pos), n)) / fabs(dot(cross(B.pos - A.pos, C.pos - A.pos), n));

		float u = alpha * A.u + beta * B.u + gamma * C.u;
		float v = alpha * A.v + beta * B.v + gamma * C.v;

		rec.u = u;
		rec.v = v;
		rec.t = t;
		rec.setFaceNormal(r, n);
		rec.mat_ptr = mat_ptr;
		rec.p = r.at(t);

		return true;
	}
}