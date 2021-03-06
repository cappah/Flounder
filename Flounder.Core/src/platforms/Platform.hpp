#pragma once

//#define STB_IMAGE_IMPLEMENTATION
//#include <stb/stb_image.h>
#define STB_IMAGE_IMPLEMENTATION
#include "../stb/stb_image.h"

#ifdef FLOUNDER_PLATFORM_WINDOWS
#include <Windows.h>
#endif

#define GLFW_INCLUDE_VULKAN
#include <glfw/glfw3.h>

#include <al/al.h>
#include <al/alc.h>

namespace Flounder
{
	class Platform
	{
	public:
		static void ErrorVk(const VkResult &result);

		static void ErrorGlfw(const int &result);

		static void ErrorAl(const ALenum &result);

		static uint32_t FindMemoryTypeIndex(const VkPhysicalDeviceMemoryProperties *deviceMemoryProperties, const VkMemoryRequirements *memoryRequirements, const VkMemoryPropertyFlags &requiredProperties);
	};
}
