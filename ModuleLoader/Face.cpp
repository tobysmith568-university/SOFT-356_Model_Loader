#include "Face.h"

using namespace std;

void Face::AddIndex(Index index)
{
	indices.push_back(index);
}

vector<Index> Face::GetIndices()
{
	return indices;
}

GLuint Face::GetOffset(std::vector<GLuint>& positions, GLuint offset)
{
	if (indices.size() == 3)
	{
		positions.push_back(2 + offset);
		positions.push_back(1 + offset);
		positions.push_back(0 + offset);

		return offset + 3;
	}

	positions.push_back(2 + offset);
	positions.push_back(1 + offset);
	positions.push_back(0 + offset);
	positions.push_back(3 + offset);
	positions.push_back(2 + offset);
	positions.push_back(0 + offset);

	return offset + 4;
}