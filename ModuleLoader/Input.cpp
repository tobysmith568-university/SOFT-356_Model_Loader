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

const std::string& Input::GetOffset()
{
	return offset;
}

void Input::SetOffset(std::string _offset)
{
	offset = _offset;
}

const std::string& Input::GetSet()
{
	return set;
}

void Input::SetSet(std::string _set)
{
	set = _set;
}

const std::vector<GLfloat> Input::GetData()
{
	return data;	
}

void Input::SetData(std::vector<GLfloat> _data)
{
	data = _data;
}
