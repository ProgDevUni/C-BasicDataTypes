@echo off
setlocal

if /I "%1"=="run" goto run
if /I "%1"=="build" goto build
if /I "%1"=="build_and_run" goto build_and_run
goto usage

:run
if exist test.exe (
    echo Running...
    echo ---------------------------
    test.exe
    echo ---------------------------
) else (
    echo No build found. Please compile first
    exit /b 1
)
goto end

:build
echo Building...
gcc test.c src\*.c -I include -o test
if %errorlevel% neq 0 (
    echo Build failed!
    exit /b %errorlevel%
)
echo Build successful!
goto end

:build_and_run
echo Building...
gcc test.c src\*.c -I include -o test
if %errorlevel% neq 0 (
    echo Build failed!
    exit /b %errorlevel%
)
echo Build successful!
echo Running...
echo ---------------------------
test.exe
echo ---------------------------
goto end

:usage
echo Unknown mode: %1
echo Usage: build [run^|build^|build_and_run]
exit /b 1

:end
endlocal
