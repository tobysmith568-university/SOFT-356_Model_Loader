#pragma once
#include <glm/glm.hpp>
#include <glm/fwd.hpp>

using namespace glm;

class MVPBuilder
{
public:
	MVPBuilder& AddScale(float x, float y, float z);
	MVPBuilder& AddRotation(float degrees, float x, float y, float z);
	MVPBuilder& AddTranslation(float x, float y, float z);
	mat4 Build();
private:
	mat4 scaleModel = mat4(1.0f);
	mat4 rotationModel = mat4(1.0f);
	mat4 translationModel = mat4(1.0f);
};