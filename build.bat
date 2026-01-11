@echo off
REM Tic Tac Toe — Build WASM with Emscripten
REM Requires: Emscripten SDK installed and emsdk_env activated

echo Building C++ to WASM...
emcc src/tic_tac_toe.cpp -O2 -s WASM=1 ^
  -s EXPORTED_FUNCTIONS="[_reset_board,_player_move,_computer_move,_get_cell,_check_winner]" ^
  -s EXTRA_EXPORTED_RUNTIME_METHODS="[cwrap]" ^
  -o web/tic_tac_toe.js

if %ERRORLEVEL% equ 0 (
  echo Build successful! Web files ready in web/
  echo.
  echo To run locally, execute:
  echo   run.bat
) else (
  echo Build failed. Check that Emscripten is installed and activated.
  echo See: https://emscripten.org/docs/getting_started/downloads.html
)
pause
