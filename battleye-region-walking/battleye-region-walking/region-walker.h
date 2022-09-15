#pragma once
#include "framework.h"

namespace BE
{
	enum RegionType : int
	{
		MEMORY_VALID,
		MEMORY_INVALID
	};

	struct RegionData
	{
		RegionType regionType = {};
		MEMORY_BASIC_INFORMATION regionMBI = {};
	};

	std::vector<RegionData> SearchMemoryRegions(void* funcToSkip);
}