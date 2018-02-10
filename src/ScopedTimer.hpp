#pragma once

#include <vulkan/vulkan.h>

#include <string>

class ScopedTimer final
{
public:
	ScopedTimer(const std::string& name, VkCommandBuffer cb);
	~ScopedTimer();

	ScopedTimer(const ScopedTimer&) = delete;

private:
	VkCommandBuffer m_cb;
};