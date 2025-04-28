@echo off

set inputfile=%1
powershell -NoProfile -Command "'%inputfile%' | .\main.exe > 'output_%inputfile%.txt'"
