#pragma once

#include <vulkan/vulkan.h>

namespace Utils
{
	uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);
	void createBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory);
	void createImage(VkImageType type, uint32_t width, uint32_t height, uint32_t depth, uint32_t layers, VkFormat format, VkImageTiling tiling, VkImageUsageFlags usage, VkMemoryPropertyFlags properties, VkImage& image, VkDeviceMemory& imageMemory);
	VkImageView createImageView(VkImage image, VkFormat format, VkImageAspectFlags aspectFlags);
	void copyBufferToImage(VkCommandBuffer cb, VkBuffer buffer, VkImage image, uint32_t width, uint32_t height);

	VkDeviceSize getFormatBPP(VkFormat format);

	VkCommandBuffer beginSingleTimeCommands();
	void endSingleTimeCommands(VkCommandBuffer cb);
}