/*
 * @Description: 纹理相关类
 * @Author: 妄想
 * @Email: long452a@163.com
 * @Date: 2020-11-10
 */

#ifndef TEXTURE_H
#define TEXTURE_H

#include "Perlin.h"

namespace disc0ver {
	class Texture {
	public:
		virtual rgb value(double u, double v, const point& p) const = 0;
	};

	class SolidColor : public Texture {
	public:
		SolidColor() = default;
		SolidColor(rgb c) : color(c) {}
		SolidColor(double r, double g, double b) : SolidColor(rgb(r, g, b)) {}

		virtual rgb value(double u, double v, const point& p) const override {
			return color;
		}
	private:
		rgb color;
	};

	class checkerTexture : public Texture {
	public:
		checkerTexture() = default;

		checkerTexture(std::shared_ptr<Texture> _even, std::shared_ptr<Texture> _odd) : even(_even), odd(_odd) {}

		checkerTexture(rgb c1, rgb c2) : even(std::make_shared<SolidColor>(c1)), odd(std::make_shared<SolidColor>(c2)) {}

		virtual rgb value(double u, double v, const point& p) const override {
			auto sines = sin(10 * p[0]) * sin(10 * p[1]) * sin(10 * p[2]);
			if (sines < 0)
				return odd->value(u, v, p);
			else
				return even->value(u, v, p);
		}
	private:
		std::shared_ptr<Texture> odd, even;
	};

	class noiseTexture : public Texture {
	public:
		noiseTexture() = default;
		noiseTexture(double sc) : scale(sc) {}

		virtual rgb value(double u, double v, const point& p) const override {
			return rgb(1, 1, 1) * 0.5 * (1 + sin(scale * p[2] + 10 * noise.turb(p)));
		}
	private:
		Perlin noise;
		double scale;
	};

	class ImageTexture : public Texture {
	public:
		const static int bytesPerPixel = 3;
		
		ImageTexture(): data(nullptr), width(0), height(0), bytesPerScanline(0) {};

		ImageTexture(const char* filename);

		~ImageTexture();

		virtual rgb value(double u, double v, const point& p) const override {
			if (data == nullptr)
				return rgb(0, 1, 1);

			u = (u < 0.0) ? 0.0 : ((u > 1.0) ? 1.0 : u);
			v = 1 - ((v < 0.0) ? 0.0 : ((v > 1.0) ? 1.0 : v));

			auto i = static_cast<int>(u * width);
			auto j = static_cast<int>(v * height);

			if (i >= width) i = width - 1;
			if (j >= height) j = height - 1;

			const auto colorScale = 1.0 / 255.0;
			auto pixel = data + j * bytesPerScanline + i * bytesPerPixel;

			return rgb(colorScale * pixel[0], colorScale * pixel[1], colorScale * pixel[2]);
		}
	private:
		unsigned char* data;
		int width, height;
		int bytesPerScanline;
	};
}

#endif // !TEXTURE_H
