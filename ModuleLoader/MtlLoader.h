#pragma once

#include "Material.h"

#include <string>

class MtlLoader
{
public:
	Material& LoadMaterial(std::string& fileLocation);
};

