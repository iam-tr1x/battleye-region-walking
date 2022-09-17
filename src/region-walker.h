#pragma once
#include "framework.h"

namespace BE
{
	enum RegionType : int
	{
		MEMORY_VALID,
		MEMORY_INVALID
	};

	std::vector<std::pair<RegionType, MEMORY_BASIC_INFORMATION>> SearchMemoryRegions(const void* funcToSkip);
}