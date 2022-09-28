#include "framework.h"
#include "region-walker.h"

int main()
{
	for (const auto& [key, value] : BE::SearchMemoryRegions(&main))
	{
		std::printf("%s Memory Region -> %p\n", key == BE::MEMORY_VALID ? "Valid" : "Invalid", value.BaseAddress);
	}

	return std::getchar();
}