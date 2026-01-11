@echo off
REM Compile the C++ console Tic Tac Toe game
REM Requires: GCC, Clang, or MSVC compiler

echo Compiling C++ Tic Tac Toe...
g++ -o tic_tac_toe.exe src/tic_tac_toe_console.cpp -std=c++11

if %ERRORLEVEL% equ 0 (
  echo Build successful!
  echo Run the game with: tic_tac_toe.exe
) else (
  echo Build failed. Make sure you have a C++ compiler installed.
  echo Install MinGW (GCC) from: https://www.mingw-w64.org/
  echo Or use Visual Studio Build Tools.
)
pause
