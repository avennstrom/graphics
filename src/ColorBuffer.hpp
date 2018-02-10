#pragma once

#include "ImageResource.hpp"

#include <string>

class ColorBuffer final
	: public ImageResource
{
public:
	ColorBuffer();
	~ColorBuffer();

	void createBackbuffer(VkImage image, VkFormat format);

	void create1D(const std::string& name, uint32_t width, VkFormat format);
	void create1DArray(const std::string& name, uint32_t width, uint32_t layers, VkFormat format);

	void create2D(const std::string& name, uint32_t width, uint32_t height, VkFormat format);
	void create2DArray(const std::string& name, uint32_t width, uint32_t height, uint32_t layers, VkFormat format);

	void transition(VkCommandBuffer cb, VkImageLayout newLayout) override;
private:
	VkDeviceMemory m_memory;
};