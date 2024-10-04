-- premake.lua

workspace "WPM"
    configurations { "Development", "RelCanditate", "Production" }
    language "C++"
    architecture "x64"

outputDir = "%{prj.name}/%{cfg.buildcfg}-%{cfg.architecture}"
objectDir = "bin-obj/%{prj.name}/%{cfg.buildcfg}-%{cfg.architecture}"

codePath = "src"

glfwLib = "C:\\Libs\\glfw-3.4.bin.WIN64\\lib-vc2022"
glfwInclude = "C:\\Libs\\glfw-3.4.bin.WIN64\\include"
imguiInclude = "C:\\Libs\\imgui-1.91.2\\backends"


-- PROJECT --
project "Manager"
    targetdir ("bin/" .. outputDir)
    objdir (objectDir)
    location "src"
    files {   
        "src/**.h",
        "src/**.hpp",
        "src/**.c",
        "src/**.cpp"
    }

    includedirs (codePath)
    includedirs (glfwInclude)
    includedirs (imguiInclude)
    
    libdirs (glfwLib)

    links ("opengl32.lib")
    links ("glfw3.lib")

    disablewarnings { "4005", "4099", "4098", "4146" }

    cppdialect "C++17"
    systemversion "latest"
    buildoptions { "/MP" } 

    filter "configurations:Development"
        kind "ConsoleApp"
        defines { "DEBUG" }
        symbols "On"

    filter "configurations:RelCanditate"
        kind "ConsoleApp"
        defines { "NDEBUG", "RC" }
        optimize "On"

    filter "configurations:Production"
        kind "WindowedApp"
        defines { "NDEBUG" }
        optimize "On"