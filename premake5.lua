workspace "CruxEngine"
   architecture "x64"

   configurations { 
	   "Debug", 
	   "Release", 
   }
   
finalDir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["GLFW"] = "Crux/3rdParty/GLFW/include"
include "Crux/3rdParty/GLFW"

project "Crux"
   location "Crux"
   kind "SharedLib"
   language "C++"

   targetdir ("build/" .. finalDir .. "/%{prj.name}")
   objdir ("build/" .. finalDir .. "/%{prj.name}")

   files { 
      "%{prj.name}/src/**.h", 
      "%{prj.name}/src/**.cpp",
   }

   includedirs {
      "{prj.name}/src",
      "%{IncludeDir.GLFW}",
   }

   links {
      "GLFW",
   }

   filter "system:linux"
      cppdialect "C++17"
      staticruntime "On"
      systemversion "latest"
      buildoptions {
         "-std=c++17", "-pthread"
      }
		postbuildcommands {
			("{COPY} %{cfg.buildtarget.relpath} ../build/" .. finalDir .. "/Sandbox")
		}


   filter "configurations:Debug"
      defines { "FL_DEBUG" }
      symbols "On"

   filter "configurations:Release"
      defines { "FL_RELEASE" }
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
      "Crux/src",
   }

   links {
      "Crux"
   }

   filter "system:linux"
      cppdialect "C++17"
      staticruntime "On"
      systemversion "latest"
      buildoptions {
         "-std=c++17", "-pthread"
      }


   filter "configurations:Debug"
      defines { "FL_DEBUG" }
      symbols "On"

   filter "configurations:Release"
      defines { "FL_NDEBUG" }
      optimize "On"