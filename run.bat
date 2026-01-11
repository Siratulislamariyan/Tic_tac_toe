@echo off
REM Start a local HTTP server to run the game
echo Starting server on http://localhost:8000
echo Press Ctrl+C to stop
cd web
python -m http.server 8000
