@echo off

:loop
cls

echo running pico8-tools.exe
echo.

bin\pico8-tools.exe
echo.

echo waiting for file changes
python bin\wait_file.py
echo.

goto loop
