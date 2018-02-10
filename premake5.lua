VULKAN_SDK = "C:/VulkanSDK/1.0.65.1/"

solution "graphics"
platforms { "x64" }
configurations { "Debug", "Release" }

project "graphics"
	language "C++"
	kind "ConsoleApp"
	architecture "x86_64"
	targetdir "bin"
	debugdir "%{cfg.targetdir}"
	objdir "obj/%{cfg.shortname}"
	files {
		"src/**.hpp",
		"src/**.cpp",

		-- Shaders
		"src/**.vert",
		"src/**.frag",
		"src/**.comp",
	}

	includedirs {
		VULKAN_SDK .. "Include",
		"extlib/glfw/include",
		"extlib/stb",
		"extlib/tinyobjloader",
		"extlib/glm/include",
	}

	libdirs {
		VULKAN_SDK .. "Lib",
		"extlib/glfw/lib",
	}

	links {
		"glfw3",
		"vulkan-1",
	}

	filter "files:**.comp or **.vert or **.frag"
		buildcommands {
			'glslangValidator -V -o "%{cfg.targetdir}/shaders/%{file.name}.spv" "%{file.abspath}"',
		}
		buildoutputs {
			'%{cfg.targetdir}/shaders/%{file.name}.spv',
		}
