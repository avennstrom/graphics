#include "Texture.hpp"
#include "Graphics.hpp"
#include "Utils.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include <stdexcept>

Texture::Texture()
{
}

Texture::~Texture()
{
	vkDestroySampler(Graphics::g_device, m_sampler, nullptr);
	vkDestroyImageView(Graphics::g_device, m_view, nullptr);
	vkDestroyImage(Graphics::g_device, m_image, nullptr);
	vkFreeMemory(Graphics::g_device, m_memory, nullptr);
}

void Texture::loadFromFile(const std::string& filename)
{
	m_imageLayout = VK_IMAGE_LAYOUT_UNDEFINED;
	m_format = VK_FORMAT_R8G8B8A8_UNORM;

	int texWidth, texHeight, texChannels;
	stbi_uc* pixels = stbi_load(filename.c_str(), &texWidth, &texHeight, &texChannels, STBI_rgb_alpha);
	VkDeviceSize imageSize = texWidth * texHeight * Utils::getFormatBPP(m_format);

	if (!pixels)
	{
		throw std::runtime_error("failed to load texture image!");
	}
	
	VkBuffer stagingBuffer;
	VkDeviceMemory stagingBufferMemory;
	Utils::createBuffer(
		imageSize, 
		VK_BUFFER_USAGE_TRANSFER_SRC_BIT, 
		VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, 
		stagingBuffer, 
		stagingBufferMemory);

	void* data;
	vkMapMemory(Graphics::g_device, stagingBufferMemory, 0, imageSize, 0, &data);
	memcpy(data, pixels, static_cast<size_t>(imageSize));
	vkUnmapMemory(Graphics::g_device, stagingBufferMemory);

	stbi_image_free(pixels);

	Utils::createImage(
		VK_IMAGE_TYPE_2D,
		texWidth, 
		texHeight, 
		1,
		1,
		m_format,
		VK_IMAGE_TILING_OPTIMAL, 
		VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_SAMPLED_BIT, 
		VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, 
		m_image, 
		m_memory);

	VkCommandBuffer cb = Utils::beginSingleTimeCommands();

	transition(cb, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL);
	Utils::copyBufferToImage(
		cb, 
		stagingBuffer, 
		m_image, 
		static_cast<uint32_t>(texWidth), 
		static_cast<uint32_t>(texHeight));
	transition(cb, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);

	Utils::endSingleTimeCommands(cb);

	vkDestroyBuffer(Graphics::g_device, stagingBuffer, nullptr);
	vkFreeMemory(Graphics::g_device, stagingBufferMemory, nullptr);

	m_view = Utils::createImageView(
		m_image, 
		VK_FORMAT_R8G8B8A8_UNORM, 
		VK_IMAGE_ASPECT_COLOR_BIT);

	VkSamplerCreateInfo samplerInfo = {};
	samplerInfo.sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO;
	samplerInfo.magFilter = VK_FILTER_LINEAR;
	samplerInfo.minFilter = VK_FILTER_LINEAR;
	samplerInfo.addressModeU = VK_SAMPLER_ADDRESS_MODE_REPEAT;
	samplerInfo.addressModeV = VK_SAMPLER_ADDRESS_MODE_REPEAT;
	samplerInfo.addressModeW = VK_SAMPLER_ADDRESS_MODE_REPEAT;
	samplerInfo.anisotropyEnable = VK_TRUE;
	samplerInfo.maxAnisotropy = 16;
	samplerInfo.borderColor = VK_BORDER_COLOR_INT_OPAQUE_BLACK;
	samplerInfo.unnormalizedCoordinates = VK_FALSE;
	samplerInfo.compareEnable = VK_FALSE;
	samplerInfo.compareOp = VK_COMPARE_OP_ALWAYS;
	samplerInfo.mipmapMode = VK_SAMPLER_MIPMAP_MODE_LINEAR;

	if (vkCreateSampler(Graphics::g_device, &samplerInfo, nullptr, &m_sampler) != VK_SUCCESS)
	{
		throw std::runtime_error("failed to create texture sampler!");
	}
}

void Texture::transition(VkCommandBuffer cb, VkImageLayout newLayout)
{
	assert(newLayout == VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL
		|| newLayout == VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);

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

	if (m_imageLayout == VK_IMAGE_LAYOUT_UNDEFINED && newLayout == VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL)
	{
		barrier.srcAccessMask = 0;
		barrier.dstAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;

		sourceStage = VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT;
		destinationStage = VK_PIPELINE_STAGE_TRANSFER_BIT;
	}
	else if (m_imageLayout == VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL && newLayout == VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL)
	{
		barrier.srcAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
		barrier.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;

		sourceStage = VK_PIPELINE_STAGE_TRANSFER_BIT;
		destinationStage = VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT;
	}
	else
	{
		throw std::invalid_argument("unsupported layout transition!");
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