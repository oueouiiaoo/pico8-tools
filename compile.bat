@echo off

echo PLEASE WAIT FOR vcvarsall.bat TO SET THE ENVIROMENT FOR THE COMPILER UP
echo.

call "C:\Program Files (x86)\Microsoft Visual Studio\2017\Community\VC\Auxiliary\Build\vcvarsall.bat" x86

:loop
cls

echo terminating pico8-tools.exe
taskkill /F /IM "pico8-tools.exe"
echo.

echo compiling main.c
cl main.c /nologo /Fe"bin/pico8-tools.exe" /I include /link /incremental:no lib/SDL2/x86/SDL2.lib
del main.obj
echo.

echo waiting for file changes
python wait_file.py
echo.

goto loop
