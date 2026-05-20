# Java Project Analyzer

Multithreaded C++ CLI tool for analyzing Java projects, built for learning purposes. Processes files in parallel and generates fun code statistics.

# Features

- Efficient multithreaded file processing
- Get number of lines-of-code, classes and methods
- Project-wide word search (TODO)

# Getting Started

## Prerequisites

- CMake (at least 3.16)
- C++ Compiler (at least C++17)

## Installing (Windows Command Prompt + MinGW)

```
git clone --recursive https://github.com/elias4096/java-project-analyzer.git
cd java-project-analyzer

mkdir build
cd build

cmake -G "MinGW Makefiles" ..
mingw32-make

# Run app
JavaProjectAnalyzer.exe

# Run tests
Tests.exe
```
