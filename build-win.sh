#!/bin/sh

x86_64-w64-mingw32-g++ src/*.cpp src/*/*.cpp src/*/*/*.cpp \
-Lthirdparty/windows/lib -Ithirdparty/windows/include -lraylibdll -O3 \
-o tetrush_win64/tetrush-win.exe --static
