#include "Input.h"

const std::string& Input::GetSemantic()
{
	return semantic;
}

void Input::SetSemantic(std::string _semantic)
{
	semantic = _semantic;
}

const std::string& Input::GetSource()
{
	return source;
}

void Input::SetSource(std::string _source)
{
	source = _source;

	if (source.size() >= 2 && source[0] == '#')
	{
		source = source.substr(1, source.size());
	}
}

const GLuint Input::GetOffset()
{
	return offset;
}

void Input::SetOffset(GLuint _offset)
{
	offset = _offset;
}

void Input::SetOffset(std::string _offset)
{
	offset = stoi(_offset);
}

const GLuint Input::GetSet()
{
	return set;
}

void Input::SetSet(GLuint _set)
{
	set = _set;
}

void Input::SetSet(std::string _set)
{
	set = stoi(_set);
}

const std::vector<GLfloat> Input::GetData()
{
	return data;	
}

void Input::SetData(std::vector<GLfloat> _data)
{
	data = _data;
}

const GLuint Input::GetDataStride()
{
	return dataStride;
}

void Input::SetDataStride(GLuint _stride)
{
	dataStride = _stride;
}
