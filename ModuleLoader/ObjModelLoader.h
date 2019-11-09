#pragma once

#include "IModelLoader.h"
#include "FileUtils.h"
#include "Face.h"
#include "Material.h"
#include "MtlLoader.h"

class ObjModelLoader : public IModelLoader
{
public:
	ObjModelLoader(FileUtils& _fileUtils, MtlLoader& _mtlLoader);
	Model& GetModel(std::string fileLocation);

private:
	FileUtils fileUtils;
	MtlLoader mtlLoader;

	void ReadSpaceSepFloats(std::vector<GLfloat>& values, std::string& line);
	void ReadFace(std::vector<Face>& faces, std::string& line);
	void ReadIndex(Face& face, char* index);
	void ReadMaterials(std::vector<Material>& materials, std::string& line, std::string& folder);

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