#include "ScopedTimer.hpp"

#include "Graphics.hpp"

ScopedTimer::ScopedTimer(const std::string& name, VkCommandBuffer cb)
	: m_cb(cb)
{
	if (Graphics::isExtensionAvailable(VK_EXT_DEBUG_MARKER_EXTENSION_NAME))
	{
		auto fn = (PFN_vkCmdDebugMarkerBeginEXT)vkGetInstanceProcAddr(Graphics::g_instance, "vkCmdDebugMarkerBeginEXT");
		VkDebugMarkerMarkerInfoEXT markerInfo = {};
		markerInfo.sType = VK_STRUCTURE_TYPE_DEBUG_MARKER_MARKER_INFO_EXT;
		markerInfo.color[0] = 1.0f;
		markerInfo.color[1] = 1.0f;
		markerInfo.color[2] = 1.0f;
		markerInfo.color[3] = 1.0f;
		markerInfo.pMarkerName = name.c_str();
		fn(cb, &markerInfo);
	}
}

ScopedTimer::~ScopedTimer()
{
	if (Graphics::isExtensionAvailable(VK_EXT_DEBUG_MARKER_EXTENSION_NAME))
	{
		auto fn = (PFN_vkCmdDebugMarkerEndEXT)vkGetInstanceProcAddr(Graphics::g_instance, "vkCmdDebugMarkerEndEXT");
		fn(m_cb);
	}
}
