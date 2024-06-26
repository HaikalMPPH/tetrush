workspace "platformer-proto"
    configurations { "Debug", "Release" }

project "platformer-proto"
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
        defines { "NDEBUG" }
        optimize "On"
