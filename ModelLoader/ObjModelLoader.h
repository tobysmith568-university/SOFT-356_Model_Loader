#pragma once

#include "IModelLoader.h"
#include "FileUtils.h"
#include "Face.h"
#include "Material.h"
#include "MtlLoader.h"
#include "ConsoleUtil.h"

class ObjModelLoader : public IModelLoader
{
public:
	ObjModelLoader(FileUtils& _fileUtils, ConsoleUtil& _consoleUtil, MtlLoader& _mtlLoader);
	void GetModel(Model& model, std::string fileLocation, GLuint& program);

private:
	FileUtils fileUtils;
	ConsoleUtil consoleUtil;
	MtlLoader mtlLoader;

	char* GetSingleString(std::string& line);
	void ReadSpaceSepFloats(std::vector<GLfloat>& values, std::string& line);
	void ReadFace(std::vector<Face>& faces, std::string& line, std::string& fileName);
	void ReadIndex(Face& face, char* index);
	void ReadMaterials(Model& model, std::string& line, std::string& folder);

	void SetVertices(Mesh& mesh,
		std::vector<GLfloat>& vertexValues,
		std::vector<GLfloat>& textureCoordValues,
		std::vector<GLfloat>& normalValues,
		std::vector<Face>& faceValues,
		std::string& fileLocation);
	void SetIndices(Mesh&, std::vector<Face>& faces);
};