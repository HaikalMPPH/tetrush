workspace "tetrush"
    configurations { "Debug", "Release" }

project "tetrush"
    kind "ConsoleApp"
    language "C++"
    toolset "clang"
    files {
        "src/*.cpp", "src/*/*.cpp", "src/*/*/*.cpp",
        "src/*.hpp", "src/*/*.hpp", "src/*/*/*.hpp"
    }
    libdirs { "./thirdparty/linux/lib" }
    includedirs { "./thirdparty/linux/include" }
    links { "raylib" }
    warnings "High"
    targetdir "./bin/%{cfg.buildcfg}"
    filter "configurations:Debug"
        defines { "DEBUG" }
        symbols "On"
    filter "configurations:Release"
        optimize "On"
