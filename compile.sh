#!/bin/bash

# Compilation script for Carbon Emission Analysis programs
# Make sure you have a C++ compiler (g++ or clang++) installed

echo ""
echo "========================================="
echo "Carbon Emission Analysis - Build Script"
echo "========================================="
echo ""

# Get the directory where this script is located
SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
cd "$SCRIPT_DIR"

# Compile Program 1 (Array-based)
echo "Compiling Program 1 (Array implementation)..."
g++ -std=c++11 \
    program1_array/main_array.cpp \
    program1_array/arraylist.cpp \
    program1_array/array_sort.cpp \
    program1_array/array_search.cpp \
    shared/csvloader.cpp \
    shared/analysis.cpp \
    shared/resident.cpp \
    -o program1_array/main_array

if [ $? -eq 0 ]; then
    echo "[OK] program1.exe created successfully!"
else
    echo "[ERROR] Failed to compile program1.exe"
    echo "Make sure g++ is installed and in your PATH"
    exit 1
fi

# Compile Program 2 (Linked List-based)
echo ""
echo "Compiling Program 2 (Linked List implementation)..."
g++ -std=c++11 \
    program2_linkedlist/main_linkedlist.cpp \
    program2_linkedlist/linkedlist.cpp \
    program2_linkedlist/linkedlist_sort.cpp \
    program2_linkedlist/linkedlist_search.cpp \
    shared/csvloader.cpp \
    shared/analysis.cpp \
    shared/resident.cpp \
    -o program2_linkedlist/main_linkedlist

if [ $? -eq 0 ]; then
    echo "[OK] program2.exe created successfully!"
else
    echo "[ERROR] Failed to compile program2.exe"
    exit 1
fi

echo ""
echo "========================================="
echo "Build Complete!"
echo "========================================="
echo ""
echo "Executables created:"
echo "  - program1.exe (Array-based implementation)"
echo "  - program2.exe (Linked List-based implementation)"
echo ""
echo "To run:"
echo "  ./program1.exe"
echo "  ./program2.exe"
echo ""
