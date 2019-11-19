#include "Face.h"

using namespace std;

void Face::AddIndex(Index index)
{
	indices.push_back(index);
}

vector<Index>& Face::GetIndices()
{
	return indices;
}

// Appends the given vector of indices with either 3 or 6 more. An offset is given, used, and then returned. It is adjusted based on the method's actions
GLuint Face::GetOffset(std::vector<GLuint>& positions, GLuint offset)
{
	if (indices.size() == 3)// If there are 3 vertices then a single triangle made of 3 indices can be added
	{
		positions.push_back(0 + offset);
		positions.push_back(1 + offset);
		positions.push_back(2 + offset);

		return offset + 3;
	}

	// Otherwise it is assumed there are 4 vertices. This means 6 indices need to be created to form 6 triangles

	positions.push_back(0 + offset);
	positions.push_back(1 + offset);
	positions.push_back(2 + offset);
	positions.push_back(0 + offset);
	positions.push_back(2 + offset);
	positions.push_back(3 + offset);

	return offset + 4;
}