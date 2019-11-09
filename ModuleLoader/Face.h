#pragma once

#include "Index.h"

#include <vector>

class Face
{
public:
	void AddIndex(Index index);
	std::vector<Index>& GetIndices();
	GLuint GetOffset(std::vector<GLuint>& positions, GLuint offset);

private:
	std::vector<Index> indices;
};