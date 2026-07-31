@echo off

cd /d "%~dp0"

echo Current folder:
cd

echo Compiling Memory Game...
g++ -std=c++17 MemoryGame.cpp -o MemoryGame.exe

if errorlevel 1 (
    echo Compilation failed.
    pause
    exit /b
)

echo Running Memory Game...
MemoryGame.exe

pause