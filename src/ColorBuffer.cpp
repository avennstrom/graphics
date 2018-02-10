#include "ColorBuffer.hpp"
#include "Utils.hpp"
#include "Graphics.hpp"

#include <cassert>

ColorBuffer::ColorBuffer()
{
}

ColorBuffer::~ColorBuffer()
{
}

void ColorBuffer::createBackbuffer(
	VkImage image, 
	VkFormat format)
{
	m_image = image;
	m_format = format;
	m_imageLayout = VK_IMAGE_LAYOUT_UNDEFINED;

	VkImageViewCreateInfo viewInfo = {};
	viewInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
	viewInfo.image = m_image;
	viewInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
	viewInfo.format = m_format;
	viewInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
	viewInfo.subresourceRange.baseMipLevel = 0;
	viewInfo.subresourceRange.levelCount = 1;
	viewInfo.subresourceRange.baseArrayLayer = 0;
	viewInfo.subresourceRange.layerCount = 1;

	VkResult result = vkCreateImageView(Graphics::g_device, &viewInfo, nullptr, &m_view);
	assert(result == VK_SUCCESS);
}

void ColorBuffer::create1D(
	const std::string& name, 
	uint32_t width, 
	VkFormat format)
{
	m_format = format;
	m_imageLayout = VK_IMAGE_LAYOUT_UNDEFINED;

	VkImageUsageFlags usage = 
		VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT |
		VK_IMAGE_USAGE_TRANSFER_DST_BIT |
		VK_IMAGE_USAGE_TRANSFER_SRC_BIT |
		VK_IMAGE_USAGE_INPUT_ATTACHMENT_BIT |
		VK_IMAGE_USAGE_SAMPLED_BIT |
		VK_IMAGE_USAGE_STORAGE_BIT;

	Utils::createImage(
		VK_IMAGE_TYPE_1D,
		width,
		1,
		1,
		1,
		m_format,
		VK_IMAGE_TILING_OPTIMAL,
		usage,
		VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT,
		m_image,
		m_memory);

	VkImageViewCreateInfo viewInfo = {};
	viewInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
	viewInfo.image = m_image;
	viewInfo.viewType = VK_IMAGE_VIEW_TYPE_1D;
	viewInfo.format = m_format;
	viewInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
	viewInfo.subresourceRange.baseMipLevel = 0;
	viewInfo.subresourceRange.levelCount = 1;
	viewInfo.subresourceRange.baseArrayLayer = 0;
	viewInfo.subresourceRange.layerCount = 1;

	VkResult result = vkCreateImageView(Graphics::g_device, &viewInfo, nullptr, &m_view);
	assert(result == VK_SUCCESS);
}

void ColorBuffer::create1DArray(
	const std::string& name, 
	uint32_t width, 
	uint32_t layers, 
	VkFormat format)
{
	m_format = format;
	m_imageLayout = VK_IMAGE_LAYOUT_UNDEFINED;

	VkImageUsageFlags usage =
		VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT |
		VK_IMAGE_USAGE_TRANSFER_DST_BIT |
		VK_IMAGE_USAGE_TRANSFER_SRC_BIT |
		VK_IMAGE_USAGE_INPUT_ATTACHMENT_BIT |
		VK_IMAGE_USAGE_SAMPLED_BIT |
		VK_IMAGE_USAGE_STORAGE_BIT;

	Utils::createImage(
		VK_IMAGE_TYPE_1D,
		width,
		1,
		1,
		layers,
		m_format,
		VK_IMAGE_TILING_OPTIMAL,
		usage,
		VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT,
		m_image,
		m_memory);

	VkImageViewCreateInfo viewInfo = {};
	viewInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
	viewInfo.image = m_image;
	viewInfo.viewType = VK_IMAGE_VIEW_TYPE_1D;
	viewInfo.format = m_format;
	viewInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
	viewInfo.subresourceRange.baseMipLevel = 0;
	viewInfo.subresourceRange.levelCount = 1;
	viewInfo.subresourceRange.baseArrayLayer = 0;
	viewInfo.subresourceRange.layerCount = 1;

	VkResult result = vkCreateImageView(Graphics::g_device, &viewInfo, nullptr, &m_view);
	assert(result == VK_SUCCESS);
}

void ColorBuffer::create2D(
	const std::string& name, 
	uint32_t width, 
	uint32_t height, 
	VkFormat format)
{
	m_format = format;
	m_imageLayout = VK_IMAGE_LAYOUT_UNDEFINED;

	VkImageUsageFlags usage =
		VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT |
		VK_IMAGE_USAGE_TRANSFER_DST_BIT |
		VK_IMAGE_USAGE_TRANSFER_SRC_BIT |
		VK_IMAGE_USAGE_INPUT_ATTACHMENT_BIT |
		VK_IMAGE_USAGE_SAMPLED_BIT |
		VK_IMAGE_USAGE_STORAGE_BIT;

	Utils::createImage(
		VK_IMAGE_TYPE_2D,
		width,
		height,
		1,
		1,
		m_format,
		VK_IMAGE_TILING_OPTIMAL,
		usage,
		VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT,
		m_image,
		m_memory);

	VkImageViewCreateInfo viewInfo = {};
	viewInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
	viewInfo.image = m_image;
	viewInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
	viewInfo.format = m_format;
	viewInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
	viewInfo.subresourceRange.baseMipLevel = 0;
	viewInfo.subresourceRange.levelCount = 1;
	viewInfo.subresourceRange.baseArrayLayer = 0;
	viewInfo.subresourceRange.layerCount = 1;

	VkResult result = vkCreateImageView(Graphics::g_device, &viewInfo, nullptr, &m_view);
	assert(result == VK_SUCCESS);

#if 0
	auto vkDebugMarkerSetObjectNameEXT = (PFN_vkDebugMarkerSetObjectNameEXT)vkGetInstanceProcAddr(Graphics::g_instance, "vkDebugMarkerSetObjectNameEXT");
	{// Name image
		VkDebugMarkerObjectNameInfoEXT debugNameInfo = {};
		debugNameInfo.sType = VK_STRUCTURE_TYPE_DEBUG_MARKER_OBJECT_NAME_INFO_EXT;
		debugNameInfo.pObjectName = name.c_str();
		debugNameInfo.object = reinterpret_cast<uint64_t>(m_image);
		debugNameInfo.objectType = VK_DEBUG_REPORT_OBJECT_TYPE_IMAGE_EXT;
		vkDebugMarkerSetObjectNameEXT(Graphics::g_device, &debugNameInfo);
	}
	{// Name memory
		VkDebugMarkerObjectNameInfoEXT debugNameInfo = {};
		debugNameInfo.sType = VK_STRUCTURE_TYPE_DEBUG_MARKER_OBJECT_NAME_INFO_EXT;
		debugNameInfo.pObjectName = name.c_str();
		debugNameInfo.object = reinterpret_cast<uint64_t>(m_memory);
		debugNameInfo.objectType = VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_MEMORY_EXT;
		vkDebugMarkerSetObjectNameEXT(Graphics::g_device, &debugNameInfo);
	}
	{// Name view
		VkDebugMarkerObjectNameInfoEXT debugNameInfo = {};
		debugNameInfo.sType = VK_STRUCTURE_TYPE_DEBUG_MARKER_OBJECT_NAME_INFO_EXT;
		debugNameInfo.pObjectName = name.c_str();
		debugNameInfo.object = reinterpret_cast<uint64_t>(m_view);
		debugNameInfo.objectType = VK_DEBUG_REPORT_OBJECT_TYPE_IMAGE_VIEW_EXT;
		vkDebugMarkerSetObjectNameEXT(Graphics::g_device, &debugNameInfo);
	}
#endif
}

void ColorBuffer::create2DArray(
	const std::string& name, 
	uint32_t width, 
	uint32_t height, 
	uint32_t layers, 
	VkFormat format)
{
	m_format = format;
	m_imageLayout = VK_IMAGE_LAYOUT_UNDEFINED;

	VkImageUsageFlags usage =
		VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT |
		VK_IMAGE_USAGE_TRANSFER_DST_BIT |
		VK_IMAGE_USAGE_TRANSFER_SRC_BIT |
		VK_IMAGE_USAGE_INPUT_ATTACHMENT_BIT |
		VK_IMAGE_USAGE_SAMPLED_BIT |
		VK_IMAGE_USAGE_STORAGE_BIT;

	Utils::createImage(
		VK_IMAGE_TYPE_2D,
		width,
		height,
		1,
		layers,
		m_format,
		VK_IMAGE_TILING_OPTIMAL,
		usage,
		VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT,
		m_image,
		m_memory);

	VkImageViewCreateInfo viewInfo = {};
	viewInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
	viewInfo.image = m_image;
	viewInfo.viewType = VK_IMAGE_VIEW_TYPE_2D_ARRAY;
	viewInfo.format = m_format;
	viewInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
	viewInfo.subresourceRange.baseMipLevel = 0;
	viewInfo.subresourceRange.levelCount = 1;
	viewInfo.subresourceRange.baseArrayLayer = 0;
	viewInfo.subresourceRange.layerCount = layers;

	VkResult result = vkCreateImageView(Graphics::g_device, &viewInfo, nullptr, &m_view);
	assert(result == VK_SUCCESS);
}

void ColorBuffer::transition(VkCommandBuffer cb, VkImageLayout newLayout)
{
	assert(newLayout == VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL
		|| newLayout == VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL
		|| newLayout == VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL
		|| newLayout == VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL
		|| newLayout == VK_IMAGE_LAYOUT_PRESENT_SRC_KHR
		|| newLayout == VK_IMAGE_LAYOUT_GENERAL);

	if (m_imageLayout == newLayout)
	{
		return;
	}

	VkImageMemoryBarrier barrier = {};
	barrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
	barrier.oldLayout = m_imageLayout;
	barrier.newLayout = newLayout;
	barrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
	barrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
	barrier.image = m_image;

	barrier.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
	barrier.subresourceRange.baseMipLevel = 0;
	barrier.subresourceRange.levelCount = 1;
	barrier.subresourceRange.baseArrayLayer = 0;
	barrier.subresourceRange.layerCount = 1;

	VkPipelineStageFlags sourceStage;
	VkPipelineStageFlags destinationStage;

	switch (m_imageLayout)
	{
		case VK_IMAGE_LAYOUT_UNDEFINED:
			barrier.srcAccessMask = 0;
			sourceStage = VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT;
			break;
		case VK_IMAGE_LAYOUT_GENERAL:
			barrier.srcAccessMask = VK_ACCESS_MEMORY_READ_BIT | VK_ACCESS_MEMORY_WRITE_BIT;
			sourceStage = VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT;
			break;
		case VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL:
			barrier.srcAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
			sourceStage = VK_PIPELINE_STAGE_TRANSFER_BIT;
			break;
		case VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL:
			barrier.srcAccessMask = VK_ACCESS_TRANSFER_READ_BIT;
			sourceStage = VK_PIPELINE_STAGE_TRANSFER_BIT;
			break;
		case VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL:
			barrier.srcAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
			sourceStage = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
			break;
		case VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL:
			barrier.srcAccessMask = VK_ACCESS_SHADER_READ_BIT;
			sourceStage = VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT | VK_PIPELINE_STAGE_COMPUTE_SHADER_BIT;
			break;
		case VK_IMAGE_LAYOUT_PRESENT_SRC_KHR:
			barrier.srcAccessMask = 0;
			sourceStage = VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT;
			break;
		default:
			throw std::runtime_error("Invalid source layout");
	}

	switch (newLayout)
	{
		case VK_IMAGE_LAYOUT_GENERAL:
			barrier.dstAccessMask = VK_ACCESS_MEMORY_READ_BIT | VK_ACCESS_MEMORY_WRITE_BIT;
			destinationStage = VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT;
			break;
		case VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL:
			barrier.dstAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
			destinationStage = VK_PIPELINE_STAGE_TRANSFER_BIT;
			break;
		case VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL:
			barrier.dstAccessMask = VK_ACCESS_TRANSFER_READ_BIT;
			destinationStage = VK_PIPELINE_STAGE_TRANSFER_BIT;
			break;
		case VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL:
			barrier.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;
			destinationStage = VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT | VK_PIPELINE_STAGE_COMPUTE_SHADER_BIT;
			break;
		case VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL:
			barrier.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
			destinationStage = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
			break;
		case VK_IMAGE_LAYOUT_PRESENT_SRC_KHR:
			barrier.dstAccessMask = 0;
			destinationStage = VK_PIPELINE_STAGE_TRANSFER_BIT;
			break;
		default:
			throw std::runtime_error("Invalid destination layout");
	}

	vkCmdPipelineBarrier(
		cb,
		sourceStage, destinationStage,
		0,
		0, nullptr,
		0, nullptr,
		1, &barrier);

	m_imageLayout = newLayout;
}
