@echo off
setlocal
REM --- @echo off: "Don't repeat what I say." Without this, the terminal would print every single command before running it, making it look messy. ---
REM --- setlocal: "What happens in Vegas, stays in Vegas." Any variables we create (like CMAKE_PATH) will be deleted when this script finishes. ---


set "CMAKE_PATH=C:\Program Files\Microsoft Visual Studio\18\Community\Common7\IDE\CommonExtensions\Microsoft\CMake\CMake\bin\cmake.exe"
REM --- 1. Define Path to CMake ---
REM --- set: Creates a nickname. Instead of typing that huge path every time, we just say %CMAKE_PATH%.---
REM --- Quotes "": Essential because the path has spaces in it ("Program Files"). Without quotes, the computer would think "Program" is the command and "Files" is an argument. ---

echo [1/2] Configuring...
"%CMAKE_PATH%" -S . -B build
REM --- 2. Configure ---
REM --- "%CMAKE_PATH%": Runs the CMake program. ---
REM --- -S .: Source. The . means "Look for CMakeLists.txt  right here in this folder."---
REM ----B build: Build. "Put all the messy temporary files in a folder named build." ---

if %errorlevel% neq 0 exit /b 1
REM ---%errorlevel%: The "Grade" the last command got. 0 = Success. Anything else = Fail. ---
REM ---neq 0: Not EQual to 0. ---
REM --- exit /b 1: "Stop the script immediately and report an error." We don't want to try building if the configuration failed!---

REM --- 3. Build ---
echo [2/2] Building..
"%CMAKE_PATH%" --build build --config Debug
REM --- --build build: "Go into the build folder and execute the plan you made earlier." ---
REM --- --config Debug: "Build a version that is easy to debug" (it includes extra info so we can step through code later). ---


echo [SUCCESS] ✅
