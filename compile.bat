@echo off
REM Compilation script for Carbon Emission Analysis programs
REM Make sure you have a C++ compiler (g++ or clang++) installed

echo.
echo =========================================
echo Carbon Emission Analysis - Build Script
echo =========================================
echo.

REM Change to the script directory
cd /d "%~dp0"

REM Compile Program 1 (Array-based)
echo Compiling Program 1 (Array implementation)...
g++ -std=c++11 ^
    program1_array/main_array.cpp ^
    program1_array/arraylist.cpp ^
    program1_array/array_sort.cpp ^
    program1_array/array_search.cpp ^
    shared/csvloader.cpp ^
    shared/analysis.cpp ^
    shared/resident.cpp ^
    shared/performance.cpp ^
    program2_linkedlist/linkedlist.cpp ^
    -o program1.exe

if %ERRORLEVEL% EQU 0 (
    echo [OK] program1.exe created successfully!
) else (
    echo [ERROR] Failed to compile program1.exe
    echo Make sure g++ is installed and in your PATH
    pause
    exit /b 1
)

REM Compile Program 2 (Linked List-based)
echo.
echo Compiling Program 2 (Linked List implementation)...
g++ -std=c++11 ^
    program2_linkedlist/main_linkedlist.cpp ^
    program2_linkedlist/linkedlist.cpp ^
    program2_linkedlist/linkedlist_sort.cpp ^
    program2_linkedlist/linkedlist_search.cpp ^
    shared/csvloader.cpp ^
    shared/analysis.cpp ^
    shared/resident.cpp ^
    shared/performance.cpp ^
    -o program2.exe

if %ERRORLEVEL% EQU 0 (
    echo [OK] program2.exe created successfully!
) else (
    echo [ERROR] Failed to compile program2.exe
    pause
    exit /b 1
)

echo.
echo =========================================
echo Build Complete!
echo =========================================
echo.
echo Executables created:
echo  - program1.exe (Array-based implementation)
echo  - program2.exe (Linked List-based implementation)
echo.
echo To run:
echo   program1.exe
echo   program2.exe
echo.
pause
