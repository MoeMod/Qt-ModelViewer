#pragma once

#include <memory>

class CMeshFile;

struct GlobalVars_s
{
	std::unique_ptr<CMeshFile> pMeshFile;
};

GlobalVars_s &GlobalVars();