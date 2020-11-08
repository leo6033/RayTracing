/*
 * @Description:
 * @Author: ����
 * @Email: long452a@163.com
 * @Date: 2020-11-02
 */


#pragma once

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

	// TODO: ��ʱʵ�� vec3�����濼�ǲ��� C++ 11 �Ժ�����Խ�����д
	template<TYPE T>
	class vec3 {
	public:
		vec3() = default;
		vec3(float e0, float e1, float e2) { e[0] = e0; e[1] = e1; e[2] = e2; }
		vec3(Vec3f v) { e[0] = v[0]; e[1] = v[1]; e[2] = v[2]; }

		
		inline float get_x() { static_assert(T == TRANSFORM, "RGB has no contribute x, please use r"); return e[0]; }
		inline float get_y() { static_assert(T == TRANSFORM, "RGB has no contribute y, please use g"); return e[1]; }
		inline float get_z() { static_assert(T == TRANSFORM, "RGB has no contribute z, please use b"); return e[2]; }
		inline float get_r() { static_assert(T == RGB, "TRANSFORM has no contribute r, please use x"); return e[0]; }
		inline float get_g() { static_assert(T == RGB, "TRANSFORM has no contribute g, please use y"); return e[1]; }
		inline float get_b() { static_assert(T == RGB, "TRANSFORM has no contribute b, please use z"); return e[2]; }

		inline void set_x(float value) { static_assert(T == TRANSFORM, "RGB has no contribute x, please use r"); e[0] = value; }
		inline void set_y(float value) { static_assert(T == TRANSFORM, "RGB has no contribute y, please use g"); e[1] = value; }
		inline void set_z(float value) { static_assert(T == TRANSFORM, "RGB has no contribute z, please use b"); e[2] = value; }
		inline void set_r(float value) { static_assert(T == RGB, "TRANSFORM has no contribute r, please use x"); e[0] = value; }
		inline void set_g(float value) { static_assert(T == RGB, "TRANSFORM has no contribute g, please use y"); e[1] = value; }
		inline void set_b(float value) { static_assert(T == RGB, "TRANSFORM has no contribute b, please use z"); e[2] = value; }

		inline const vec3& operator+() const { return *this; }
		inline vec3 operator-() const { return vec3(-e[0], -e[1], -e[2]); }
		inline float operator[](int i) const { return e[i]; }
		inline float& operator[] (int i) { return e[i]; }
		template<typename type> inline vec3& operator=(Vec3<type> v) { return vec3(v.n[0], v.n[1], v.n[2]); }

		inline vec3& operator+=(const vec3& v) { e[0] += v.e[0]; e[1] += v.e[1]; e[2] += v.e[2]; return *this; }
		inline vec3& operator-=(const vec3& v) { e[0] -= v.e[0]; e[1] -= v.e[1]; e[2] -= v.e[2]; return *this; }
		inline vec3& operator*=(const vec3& v) { e[0] *= v.e[0]; e[1] *= v.e[1]; e[2] *= v.e[2]; return *this; }
		inline vec3& operator/=(const vec3& v) { e[0] /= v.e[0]; e[1] /= v.e[1]; e[2] /= v.e[2]; return *this; }

		template<typename type> inline vec3& operator*=(const type t) { e[0] *= t; e[1] *= t; e[2] *= t; return *this; }
		template<typename type> inline vec3& operator/=(const type t) { float k = 1.0 / t; e[0] *= k; e[1] *= k; e[2] *= k; return *this; }

		inline float length() const { return sqrt(e[0] * e[0] + e[1] * e[1] + e[2] * e[2]); }
		inline float squared_length() const { return e[0] * e[0] + e[1] * e[1] + e[2] * e[2]; }
		inline void normalize();
		
		float e[3];
		__declspec(property(get = get_x, put = set_x)) float x;
		__declspec(property(get = get_y, put = set_y)) float y;
		__declspec(property(get = get_z, put = set_z)) float z;
		__declspec(property(get = get_r, put = set_r)) float r;
		__declspec(property(get = get_g, put = set_g)) float g;
		__declspec(property(get = get_b, put = set_b)) float b;
	};

	using Rotation = vec3<TRANSFORM>;
	using Position = vec3<TRANSFORM>;
	using Scale = vec3<TRANSFORM>;
	using point = vec3<TRANSFORM>;
	using rgb = vec3<RGB>;
	
	template<TYPE T>
	inline void vec3<T>::normalize(){
		float len = this->length();
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

	template<TYPE T, typename type> inline vec3<T> operator/(const vec3<T>& v, type t) {
		return vec3<T>(v.e[0] / t, v.e[1] / t, v.e[2] / t);
	}

	template<TYPE T> inline float dot(const vec3<T>& v1, const vec3<T>& v2) {
		return v1.e[0] * v2.e[0] + v1.e[1] * v2.e[1] + v1.e[2] * v2.e[2];
	}

	inline vec3<TRANSFORM> cross(const vec3<TRANSFORM>& v1, const vec3<TRANSFORM>& v2) {
		return vec3<TRANSFORM>( (v1.e[1] * v2.e[2] - v1.e[2] * v2.e[1]),
							   -(v1.e[0] * v2.e[2] - v1.e[2] * v2.e[0]),
			                    (v1.e[0] * v2.e[1] - v1.e[1] * v2.e[0]));
	}

 }
#endif // !DGM_H
