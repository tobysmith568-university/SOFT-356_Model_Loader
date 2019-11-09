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