/*
 * @Description:
 * @Author: 妄想
 * @Email: long452a@163.com
 * @Date: 2020-11-02
 */


#pragma once

#ifndef M_PI
#define M_PI 3.141592653589793238462643383279502f
#endif

#ifndef DGM_H
#define DGM_H

#include <algorithm>
#include <iostream>
#include "vec.h"

namespace disc0ver {
	enum TYPE
	{
		TRANSFORM,
		RGB
	};

	// TODO: 暂时实现 vec3，后面考虑采用 C++ 11 以后的特性进行重写
	template<TYPE T>
	class vec3 {
	public:
		vec3() = default;
		vec3(double e0, double e1, double e2) { e[0] = e0; e[1] = e1; e[2] = e2; }
		vec3(Vec3f v) { e[0] = v[0]; e[1] = v[1]; e[2] = v[2]; }

		
		inline double get_x() const { static_assert(T == TRANSFORM, "RGB has no contribute x, please use r"); return e[0]; }
		inline double get_y() const { static_assert(T == TRANSFORM, "RGB has no contribute y, please use g"); return e[1]; }
		inline double get_z() const { static_assert(T == TRANSFORM, "RGB has no contribute z, please use b"); return e[2]; }
		inline double get_r() const { static_assert(T == RGB, "TRANSFORM has no contribute r, please use x"); return e[0]; }
		inline double get_g() const { static_assert(T == RGB, "TRANSFORM has no contribute g, please use y"); return e[1]; }
		inline double get_b() const { static_assert(T == RGB, "TRANSFORM has no contribute b, please use z"); return e[2]; }

		inline void set_x(double value) { static_assert(T == TRANSFORM, "RGB has no contribute x, please use r"); e[0] = value; }
		inline void set_y(double value) { static_assert(T == TRANSFORM, "RGB has no contribute y, please use g"); e[1] = value; }
		inline void set_z(double value) { static_assert(T == TRANSFORM, "RGB has no contribute z, please use b"); e[2] = value; }
		inline void set_r(double value) { static_assert(T == RGB, "TRANSFORM has no contribute r, please use x"); e[0] = value; }
		inline void set_g(double value) { static_assert(T == RGB, "TRANSFORM has no contribute g, please use y"); e[1] = value; }
		inline void set_b(double value) { static_assert(T == RGB, "TRANSFORM has no contribute b, please use z"); e[2] = value; }

		inline const vec3& operator+() const { return *this; }
		inline vec3 operator-() const { return vec3(-e[0], -e[1], -e[2]); }
		inline double operator[](int i) const { return e[i]; }
		inline double& operator[] (int i) { return e[i]; }
		template<typename type> inline vec3 operator=(Vec3<type> v) { return vec3(v.n[0], v.n[1], v.n[2]); }

		inline vec3& operator+=(const vec3& v) { e[0] += v.e[0]; e[1] += v.e[1]; e[2] += v.e[2]; return *this; }
		inline vec3& operator-=(const vec3& v) { e[0] -= v.e[0]; e[1] -= v.e[1]; e[2] -= v.e[2]; return *this; }
		inline vec3& operator*=(const vec3& v) { e[0] *= v.e[0]; e[1] *= v.e[1]; e[2] *= v.e[2]; return *this; }
		inline vec3& operator/=(const vec3& v) { e[0] /= v.e[0]; e[1] /= v.e[1]; e[2] /= v.e[2]; return *this; }

		template<typename type> inline vec3& operator*=(const type t) { e[0] *= t; e[1] *= t; e[2] *= t; return *this; }
		template<typename type> inline vec3& operator/=(const type t) { double k = 1.0 / t; e[0] *= k; e[1] *= k; e[2] *= k; return *this; }

		inline double length() const { return sqrt(e[0] * e[0] + e[1] * e[1] + e[2] * e[2]); }
		inline double squared_length() const { return e[0] * e[0] + e[1] * e[1] + e[2] * e[2]; }
		inline void normalize();
		bool near_zero() const {
			// Return true if the vector is close to zero in all dimensions.
			const auto s = 1e-8;
			return (fabs(e[0]) < s) && (fabs(e[1]) < s) && (fabs(e[2]) < s);
		}
		
		double e[3];
		__declspec(property(get = get_x, put = set_x)) double x;
		__declspec(property(get = get_y, put = set_y)) double y;
		__declspec(property(get = get_z, put = set_z)) double z;
		__declspec(property(get = get_r, put = set_r)) double r;
		__declspec(property(get = get_g, put = set_g)) double g;
		__declspec(property(get = get_b, put = set_b)) double b;
	};

	using Rotation = vec3<TRANSFORM>;
	using Position = vec3<TRANSFORM>;
	using Scale = vec3<TRANSFORM>;
	using point = vec3<TRANSFORM>;
	using rgb = vec3<RGB>;
	
	template<TYPE T>
	inline void vec3<T>::normalize(){
		double len = this->length();
		for (int i = 0; i < 3; i++) {
			e[i] /= len;
		}
	}

	template<TYPE T> inline std::istream& operator>>(std::istream& is, vec3<T>& t) {
		is >> t.e[0] >> t.e[1] >> t.e[2];
		return is;
	}

	template<TYPE T> inline std::ostream& operator<<(std::ostream& os, const vec3<T>& t) {
		os << t.e[0] << " " << t.e[1] << " " << t.e[2];
		return os;
	}

	template<TYPE T> inline vec3<T> operator+(const vec3<T>& v1, const vec3<T> v2) {
		return vec3<T>(v1.e[0] + v2.e[0], v1.e[1] + v2.e[1], v1.e[2] + v2.e[2]);
	}

	template<TYPE T> inline vec3<T> operator-(const vec3<T>& v1, const vec3<T> v2) {
		return vec3<T>(v1.e[0] - v2.e[0], v1.e[1] - v2.e[1], v1.e[2] - v2.e[2]);
	}

	template<TYPE T> inline vec3<T> operator*(const vec3<T>& v1, const vec3<T> v2) {
		return vec3<T>(v1.e[0] * v2.e[0], v1.e[1] * v2.e[1], v1.e[2] * v2.e[2]);
	}

	template<TYPE T> inline vec3<T> operator/(const vec3<T>& v1, const vec3<T> v2) {
		return vec3<T>(v1.e[0] / v2.e[0], v1.e[1] / v2.e[1], v1.e[2] / v2.e[2]);
	}
	
	template<TYPE T, typename type> inline vec3<T> operator*(const vec3<T>& v, type t) {
		return vec3<T>(v.e[0] * t, v.e[1] * t, v.e[2] * t);
	}

	template<TYPE T, typename type> inline vec3<T> operator*(type t, const vec3<T>& v) {
		return vec3<T>(v.e[0] * t, v.e[1] * t, v.e[2] * t);
	}

	template<TYPE T, typename type> inline vec3<T> operator/(const vec3<T>& v, type t) {
		return vec3<T>(v.e[0] / t, v.e[1] / t, v.e[2] / t);
	}

	template<TYPE T> inline double dot(const vec3<T>& v1, const vec3<T>& v2) {
		return v1.e[0] * v2.e[0] + v1.e[1] * v2.e[1] + v1.e[2] * v2.e[2];
	}

	inline vec3<TRANSFORM> cross(const vec3<TRANSFORM>& v1, const vec3<TRANSFORM>& v2) {
		return vec3<TRANSFORM>( (v1.e[1] * v2.e[2] - v1.e[2] * v2.e[1]),
							   -(v1.e[0] * v2.e[2] - v1.e[2] * v2.e[0]),
			                    (v1.e[0] * v2.e[1] - v1.e[1] * v2.e[0]));
	}

	inline double random_double() {
		// Returns a random real in [0,1).
		return rand() / (RAND_MAX + 1.0);
	}

	inline double random_double(double min, double max) {
		// Returns a random real in [min,max).
		return min + (max - min) * random_double();
	}

	inline int random_int(int min, int max) {
		// Returns a random integer in [min,max].
		return static_cast<int>(random_double(min, (double)max + 1));
	}

	template<TYPE T> inline vec3<T> randomInUnitDisk() {
		while (true) {
			vec3<T> p = vec3<T>(random_double(-1, 1), random_double(-1, 1), 0);
			if (p.length() >= 1) continue;
			return p;
		}
	}

	template<TYPE T> inline vec3<T> randomInUnitSphere(double min = -1.0f, double max = 1.0f) {
		while (true) {
			vec3<T> p = vec3<T>(random_double(min, max), random_double(min, max), random_double(min, max));
			if (p.length() >= 1)continue;
			return p;
		}
	}

	template<TYPE T>inline vec3<T> randomUnitVector() {
		vec3<T> p = randomInUnitSphere<T>();
		p.normalize();
		return p;
	}

	inline vec3<TRANSFORM> reflect(const vec3<TRANSFORM>& v, const vec3<TRANSFORM>& n) {
		return v - 2 * dot(v, n) * n;
	}

	inline vec3<TRANSFORM> refract(const vec3<TRANSFORM>& v, const vec3<TRANSFORM>& n, double eta) {
		auto cosTheta = fmin(dot(-v, n), 1.0f);
		vec3<TRANSFORM> rOutPerp = eta * (v + cosTheta * n);
		vec3<TRANSFORM> rOutParallel = -std::sqrt(std::fabs(1.0 - rOutPerp.squared_length())) * n;
		return rOutPerp + rOutParallel;
	}
 }
#endif // !DGM_H
