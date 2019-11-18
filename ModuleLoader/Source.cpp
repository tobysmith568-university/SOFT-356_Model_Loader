#include "Source.h"

const std::vector<GLfloat> Source::GetData()
{
	return data;
}

void Source::SetData(std::vector<GLfloat> _data)
{
	data = _data;
}

const GLuint Source::GetStride()
{
	return stride;
}

void Source::SetStride(GLuint _stride)
{
	stride = _stride;
}
