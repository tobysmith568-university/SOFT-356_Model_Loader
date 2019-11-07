#include "MVPBuilder.h"

#include <glm/fwd.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/matrix_clip_space.hpp>

using namespace glm;

MVPBuilder& MVPBuilder::AddScale(float x, float y, float z)
{
	scaleModel = scale(scaleModel, glm::vec3(x, y, z));
	return *this;
}

MVPBuilder& MVPBuilder::AddRotation(float degrees, float x, float y, float z)
{
	rotationModel = glm::rotate(rotationModel, radians(degrees), vec3(x, y, z));
	return *this;
}

MVPBuilder& MVPBuilder::AddTranslation(float x, float y, float z)
{
	translationModel = glm::translate(translationModel, vec3(x, y, z));
	return *this;
}

mat4 MVPBuilder::Build()
{
	// creating the view matrix
	mat4 view = glm::mat4(1.0f);
	view = translate(view, vec3(0.0f, 0.0f, -2.0f));

	// creating the projection matrix
	mat4 projection = perspective(45.0f, 4.0f / 3, 0.1f, 20.0f);

	// Adding all matrices up to create combined matrix
	mat4 mvp = projection * view * translationModel * rotationModel * scaleModel;

	return mvp;
}