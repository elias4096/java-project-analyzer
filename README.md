# Java Project Analyzer

Multithreaded C++ CLI tool for analyzing Java projects, built for learning purposes. Processes files in parallel and generates fun code statistics.

# Features

- Efficient multithreaded file processing
- Get number of lines-of-code, classes and methods
- Project-wide word search

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
analyzer.exe

# Run tests
Tests.exe
```

## Usage

```
# Uses current working directory
analyzer.exe

# Specify directory using the --path argument
analyzer.exe --path [java-project-path]

# Search through all project files using the --search argument
analyzer.exe --path [java-project-path] --search [search-term]
```
