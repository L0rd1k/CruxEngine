workspace "FlowEngine"
   architecture "x64"
   configurations { 
	"Debug", 
	"Release", 
   }

finalDir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["GLFW"] = "Flow/3rdParty/GLFW/include"
IncludeDir["GLAD"] = "Flow/3rdParty/GLAD/include"

include "Flow/3rdParty/glfw.lua"
include "Flow/3rdParty/glad.lua"


project "Flow"
   location "Flow"
   kind "SharedLib"
   language "C++"

   targetdir ("build/" .. finalDir .. "/%{prj.name}")
   objdir ("build/" .. finalDir .. "/%{prj.name}")


   files { 
      "%{prj.name}/src/**.h", 
      "%{prj.name}/src/**.cpp" 
   }

   includedirs {
      "%{IncludeDir.GLFW}",
      "%{IncludeDir.GLAD}"
   }

   links {
      "GLFW",
      "GLAD",
   }

   filter "system:linux"
      cppdialect "C++17"
      staticruntime "On"
      systemversion "latest"

   filter "configurations:Debug"
      defines { "FL_DEBUG" }
      symbols "On"

   filter "configurations:Release"
      defines { "FL_NDEBUG" }
      optimize "On"

project "Sandbox"
   location "Sandbox"
   kind "ConsoleApp"
   language "C++"

   targetdir ("build/" .. finalDir .. "/%{prj.name}")
   objdir ("build/" .. finalDir .. "/%{prj.name}")


   files { 
      "%{prj.name}/**.h", 
      "%{prj.name}/**.cpp" 
   }

   includedirs {
      "Flow/src"
   }

   links {
      "Flow"
   }

   filter "system:linux"
      cppdialect "C++17"
      staticruntime "On"
      systemversion "latest"


   filter "configurations:Debug"
      defines { "FL_DEBUG" }
      symbols "On"

   filter "configurations:Release"
      defines { "FL_NDEBUG" }
      optimize "On"