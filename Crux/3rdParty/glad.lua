project "GLAD"
	kind "StaticLib"
	language "C"
	staticruntime "off"

	targetdir ("build/" .. finalDir .. "/%{prj.name}")
	objdir ("build/" .. finalDir .. "/%{prj.name}")

	files
	{
        "GLAD/include/glad/glad.h",
        "GLAD/include/KHR/khrplatform.h",
        "GLAD/src/glad.c",
	}

    includedirs
    {
        "GLAD/include"
    }
	
	filter "system:linux"
		pic "On"

		systemversion "latest"

		defines
		{
			"_GLAD_X11"
		}

	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		runtime "Release"
		optimize "on"
