workspace "tetrush"
    configurations { "Debug", "Release" }

project "tetrush"
    kind "ConsoleApp"
    language "C++"
    toolset "clang"
    links { "raylib" }
    warnings "High"
    targetdir "bin/%{cfg.buildcfg}"
    files {
        "src/*.cpp", "src/*/*.cpp", "src/*/*/*.cpp",
        "src/*.hpp", "src/*/*.hpp", "src/*/*/*.hpp"
    }
    filter "configurations:Debug"
        defines { "DEBUG" }
        symbols "On"
    filter "configurations:Release"
        optimize "On"
