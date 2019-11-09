#pragma once

#include "IModelLoader.h"
#include "FileUtils.h"
#include "Face.h"

#include <regex>

class ObjModelLoader : public IModelLoader
{
public:
	ObjModelLoader(FileUtils& fileUtils);
	Model& GetModel(std::string fileLocation);

private:
	FileUtils fileUtils;

	void ReadSpaceSepFloats(std::vector<GLfloat>& values, std::string& line);
	void ReadFace(std::vector<Face>& faces, std::string& line);
	void ReadIndex(Face& face, char* index);

	void SetVertices(Model& model,
		std::vector<GLfloat>& vertexValues,
		std::vector<GLfloat>& textureCoordValues,
		std::vector<GLfloat>& normalValues,
		std::vector<Face>& faceValues);
	void SetIndices(Model& model, std::vector<Face>& faces);
	void SetTextures(Model& model, std::string& fileLocation);

	std::string GetTextureName(std::string& fileLocation);
	Texture LoadTexture(std::string textureLocation);
};