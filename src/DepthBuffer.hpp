#pragma once

#include "ImageResource.hpp"

#include <string>

class DepthBuffer final
	: public ImageResource
{
public:
	DepthBuffer();
	~DepthBuffer();

	void create(const std::string& name, uint32_t width, uint32_t height, VkFormat format);
	void transition(VkCommandBuffer cb, VkImageLayout newLayout) override;
private:
	VkDeviceMemory m_memory;
};