#pragma once

#include <vulkan/vulkan.h>

#include <set>

namespace Graphics
{
	extern VkInstance g_instance;
	extern VkDevice g_device;
	extern VkPhysicalDevice g_physicalDevice;
	extern VkQueue g_graphicsQueue;
	extern VkCommandPool g_commandPool;
	extern std::set<size_t> g_availableExtensions;

	bool isExtensionAvailable(const std::string& name);
};