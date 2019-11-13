#pragma once

#include "Model.h"
#include "FileUtils.h"

class BasicModelExporter
{
public:
	BasicModelExporter(FileUtils& _fileUtils);
	void Export(Model& model);

private:
	FileUtils fileUtils;
};