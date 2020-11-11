/*
 * @Description: 定义场景
 * @Author: 妄想
 * @Email: long452a@163.com
 * @Date: 2020-11-10
 */

#pragma once
#ifndef UTIL_H
#define UTIL_H

#include "scene/Scene.h"
#include "scene/Texture.h"
#include "scene/Material.h"
#include "sceneObjects/Sphere.h"

#include <string>

namespace disc0ver {

	Scene* LoadScene(std::string s);
	Scene* twoSpheres();
	Scene* twoPerlinSpheres();
}

#endif // !UTIL_H
