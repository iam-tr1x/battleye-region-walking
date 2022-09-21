#include "framework.h"
#include "region-walker.h"

int main()
{
	for (const auto& [key, value] : BE::SearchMemoryRegions(&main))
	{
		switch (key)
		{
			case BE::RegionType::MEMORY_VALID:
			{
				std::printf("Valid Memory Region: %p\n", value.BaseAddress);
				break;
			}
			case BE::RegionType::MEMORY_INVALID:
			{
				std::printf("Invalid Memory Region: %p\n", value.BaseAddress);
				break;
			}
		}
	}

	return 0;
}