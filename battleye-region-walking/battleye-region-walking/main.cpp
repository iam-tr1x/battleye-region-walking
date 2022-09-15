#include "framework.h"
#include "region-walker.h"

int main()
{
	for (const auto& it : BE::SearchMemoryRegions(main))
	{
		switch (it.regionType)
		{
		    case BE::RegionType::MEMORY_VALID:
			{
				std::printf("Valid Memory Region: %p\n", it.regionMBI.BaseAddress);
				break;
			}
			case BE::RegionType::MEMORY_INVALID:
			{
				std::printf("Invalid Memory Region: %p\n", it.regionMBI.BaseAddress);
				break;
			}
			default:
			{
				std::printf("Unknown Memory RegionType!\n");
				break;
			}
		}
	}

	return 0;
}