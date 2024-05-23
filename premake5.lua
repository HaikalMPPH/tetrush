workspace "tetris-proto"
    configurations { "Debug", "Release" }

project "tetris-proto"
    kind "ConsoleApp"
    language "C++"
    toolset "clang"
    links { "raylib" }
    warnings "High"
    targetdir "bin/%{cfg.buildcfg}"
    files {
        "src/*.cpp",
        "src/*.hpp"
    }
    filter "configurations:Debug"
        defines { "DEBUG" }
        symbols "On"
    filter "configurations:Release"
        defines { "NDEBUG" }
        optimize "On"
