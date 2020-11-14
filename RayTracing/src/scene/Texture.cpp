/*
 * @Description: 纹理相关类
 * @Author: 妄想
 * @Email: long452a@163.com
 * @Date: 2020-11-11
 */

#include "Texture.h"
#include "../fileio/rtw_stb_image.h"

namespace disc0ver {
	ImageTexture::ImageTexture(const char* filename) {
		auto componentsPerPixel = bytesPerPixel;
		data = stbi_load(filename, &width, &height, &componentsPerPixel, componentsPerPixel);

		if (!data) {
			std::cerr << "ERROR: Could not load texture image file '" << filename << "'.\n";
			width = height = 0;
		}

		bytesPerScanline = bytesPerPixel * width;
	}

	ImageTexture::~ImageTexture() {
		STBI_FREE(data);
	}

	void saveImage(const char* filename, int  Width, int  Height, int Channels, unsigned char* Output, bool open = true)
	{
		//保存为png,也可以调用stbi_write_bmp 保存为bmp
		stbi_write_png(filename, Width, Height, Channels, Output, 0);
	}
}