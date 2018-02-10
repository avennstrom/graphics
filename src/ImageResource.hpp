#pragma once

#include <vulkan/vulkan.h>

class ImageResource abstract
{
public:
	virtual void transition(VkCommandBuffer cb, VkImageLayout newLayout) = 0;

	inline VkImage image() const { return m_image; }
	inline VkImageView view() const { return m_view; }
	inline VkFormat format() const { return m_format; }
	inline VkImageLayout layout() const { return m_imageLayout; }

	inline void setLayout(VkImageLayout layout) { m_imageLayout = layout; }

protected:
	ImageResource()
		: m_image(VK_NULL_HANDLE)
		, m_view(VK_NULL_HANDLE)
		, m_imageLayout(VK_IMAGE_LAYOUT_UNDEFINED)
		, m_format(VK_FORMAT_UNDEFINED)
	{
	}

	VkImage m_image;
	VkImageView m_view;
	VkImageLayout m_imageLayout;
	VkFormat m_format;
};