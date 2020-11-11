/*
 * @Description: perlin ÔëÉù
 * @Author: ÍýÏë
 * @Email: long452a@163.com
 * @Date: 2020-11-11
 */

#ifndef PERLIN_H
#define PERLIN_H

#include "../vecmath/DGM.h"

namespace disc0ver {
	class Perlin {
	public:
		Perlin() {
			ranVec = new vec3<TRANSFORM>[pointCount];
			for (int i = 0; i < pointCount; i++) {
				ranVec[i] = vec3<TRANSFORM>(random_double(-1, 1), random_double(-1, 1), random_double(-1, 1));
				ranVec[i].normalize();
			}

			permX = perlinGeneratePerm();
			permY = perlinGeneratePerm();
			permZ = perlinGeneratePerm();
		}

		~Perlin() {
			delete[] ranVec;
			delete[] permX;
			delete[] permY;
			delete[] permY;
		}

		double noise(const point& p) const{
			auto u = p[0] - floor(p[0]);
			auto v = p[1] - floor(p[1]);
			auto w = p[2] - floor(p[2]);
			auto i = static_cast<int>(floor(p[0]));
			auto j = static_cast<int>(floor(p[1]));
			auto k = static_cast<int>(floor(p[2]));
			vec3<TRANSFORM> c[2][2][2];

			for (int di = 0; di < 2; di++) {
				for (int dj = 0; dj < 2; dj++) {
					for (int dk = 0; dk < 2; dk++) {
						c[di][dj][dk] = ranVec[
							permX[(i + di) & 255] ^
							permY[(j + dj) & 255] ^
							permZ[(k + dk) & 255]
						];
					}
				}
			}
			return perlinInterp(c, u, v, w);
		}

		double turb(const point& p, int depth = 7) const {
			auto accum = 0.0;
			auto tmpP = p;
			auto weight = 1.0;

			for (int i = 0; i < depth; i++) {
				accum += weight * noise(tmpP);
				weight *= 0.5;
				tmpP *= 2;
			}
			return fabs(accum);
		}
	private:
		static const int pointCount = 256;
		vec3<TRANSFORM>* ranVec;
		int *permX, *permY, *permZ;

		static int* perlinGeneratePerm() {
			auto p = new int[pointCount];

			for (int i = 0; i < pointCount; i++)
				p[i] = i;

			permute(p, pointCount);
			return p;
		}

		static void permute(int* p, int n) {
			for (int i = n - 1; i > 0; i--) {
				int target = random_int(0, i);
				int tmp = p[i];
				p[i] = p[target];
				p[target] = tmp;
			}
		}

		static double perlinInterp(vec3<TRANSFORM> c[2][2][2], double u, double v, double w) {
			auto uu = u * u * (3 - 2 * u);
			auto vv = v * v * (3 - 2 * v);
			auto ww = w * w * (3 - 2 * w);
			auto accum = 0.0;

			for (int i = 0; i < 2; i++) {
				for (int j = 0; j < 2; j++) {
					for (int k = 0; k < 2; k++) {
						vec3<TRANSFORM> weightV(u - i, v - j, w - k);
						accum += (i * uu + (1 - (double)i) * (1 - uu)) *
							(j * vv + (1 - (double)j) * (1 - vv)) *
							(k * ww + (1 - (double)k) * (1 - ww)) * dot(c[i][j][k], weightV);
					}
				}
			}
			return accum;
		}
	};
}

#endif // !PERLIN_H
