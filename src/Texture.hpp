#pragma once

#include "ImageResource.hpp"

#include <string>

class Texture final
	: public ImageResource
{
public:
	Texture();
	~Texture();

	void loadFromFile(const std::string& filename);
	void transition(VkCommandBuffer cb, VkImageLayout newLayout) override;

	inline VkImageView view() const { return m_view; }
	inline VkSampler sampler() const { return m_sampler; }

private:
	VkImage m_image;
	VkDeviceMemory m_memory;
	VkImageView m_view;
	VkSampler m_sampler;
};