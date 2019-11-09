#pragma once

#include "Index.h"

#include <vector>

class Face
{
public:
	void AddIndex(Index index);
	std::vector<Index> GetIndices();

private:
	std::vector<Index> indices;
};