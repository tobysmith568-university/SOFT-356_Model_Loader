#include "Vertex.h"

Vertex::Vertex()
{
	position = vec3();
	texture = vec2();
	normal = vec3();
	colour = vec4(1.0f);
}

void Vertex::SetPosition(GLfloat x, GLfloat y, GLfloat z)
{
	position.x = x;
	position.y = y;
	position.z = z;
}

void Vertex::SetTexture(GLfloat x, GLfloat y)
{
	texture.x = x;
	texture.y = y;
}

void Vertex::SetNormal(GLfloat x, GLfloat y, GLfloat z)
{
	normal.x = x;
	normal.y = y;
	normal.z = z;
}

void Vertex::SetColour(GLfloat r, GLfloat g, GLfloat b, GLfloat a)
{
	colour.r = r;
	colour.g = g;
	colour.b = b;
	colour.a = a;
}