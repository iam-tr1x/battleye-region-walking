#include "region-walker.h"

namespace BE
{
	std::vector<RegionData> SearchMemoryRegions(void* funcToSkip)
	{
		MEMORY_BASIC_INFORMATION MBI = {};
		std::vector<RegionData> tempRegionData = {};

		for (auto it = MBI.BaseAddress; VirtualQuery(it, &MBI, sizeof(MEMORY_BASIC_INFORMATION)); *reinterpret_cast<std::uint64_t*>(&it) += MBI.RegionSize)
		{
			if (MBI.State == MEM_COMMIT &&
				(MBI.Protect == PAGE_EXECUTE || MBI.Protect == PAGE_EXECUTE_READ || MBI.Protect == PAGE_EXECUTE_READWRITE &&
					(MBI.Type != MEM_PRIVATE || MBI.RegionSize != 0x10000 &&
						MBI.RegionSize != 0x20000 &&
						MBI.RegionSize != 0xF0000 &&
						MBI.RegionSize != 0x90000 &&
						MBI.RegionSize != 0xA0000)) &&
				(MBI.BaseAddress > funcToSkip || reinterpret_cast<void*>(static_cast<char*>(MBI.BaseAddress) + MBI.RegionSize) <= funcToSkip) &&
				(MBI.Protect != PAGE_EXECUTE_READWRITE || MBI.RegionSize != 0x18000))
			{
				if (MBI.Type == MEM_PRIVATE || MBI.Type == MEM_MAPPED)
				{
					if (MBI.RegionSize >= 0x11000
						|| MBI.RegionSize >= 0x4000
						&& (reinterpret_cast<std::int64_t>(MBI.BaseAddress) & 0xFF0000000000) != 0x7F0000000000
						&& (reinterpret_cast<std::int64_t>(MBI.BaseAddress) & 0xFFF000000000) != 0x7F000000000
						&& MBI.RegionSize != 0x10000
						&& (reinterpret_cast<std::int64_t>(MBI.BaseAddress) & 0xFFFFF0000000i64) != 0x70000000
						&& (MBI.BaseAddress != reinterpret_cast<void*>(0x3E0000) || MBI.RegionSize != 0xF000)
						&& (MBI.BaseAddress != reinterpret_cast<void*>(0x3F0000) || MBI.RegionSize != 0x4000))
					{
						tempRegionData.push_back({ RegionType::MEMORY_INVALID, MBI });
						continue;
					}
				}
			}
			tempRegionData.push_back({ RegionType::MEMORY_VALID, MBI });
		}

		return tempRegionData;
	}
}