#pragma once

#include <string>
#include <vector>

#include "GLFW/glfw3.h"

class Input
{
public:
	const std::string& GetSemantic();
	void SetSemantic(std::string _semantic);

	const std::string& GetSource();
	void SetSource(std::string _source);

	const std::string& GetOffset();
	void SetOffset(std::string _offset);

	const std::string& GetSet();
	void SetSet(std::string _set);

	const std::vector<GLfloat> GetData();
	void SetData(std::vector<GLfloat> _data);

private:
	std::string semantic;
	std::string source;
	std::string offset;
	std::string set;

	std::vector<GLfloat> data;
};