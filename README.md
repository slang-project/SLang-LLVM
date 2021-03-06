﻿# SLang-LLVM

## Overview

This project is an implementation of the SLang programming language backend using LLVM.
You may find an old implementation on the [branch `v0.1.3`](../../tree/v0.1.3).

## How to install dependencies and build project

This project is based on CMake. In order to build it, you need to install dependencies and then build the project.

### Windows

_Note_: Visual Studio 2019 is recommended. Older versions require some additional CMake environment setup.

* [Visual Studio 2019](https://visualstudio.microsoft.com/vs)
    * Install "Individual components" (usually added with workload "Desktop development with C++")
        * MSVC v142
        * C++ CMake tools for Windows
* [Vcpkg](https://github.com/Microsoft/vcpkg)
    * `.\vcpkg integrate install`
    * Install dependencies
        * `.\vcpkg install nlohmann-json`
* [LLVM 9.0.1](https://github.com/llvm/llvm-project/releases/tag/llvmorg-9.0.1)
    * _**TODO**: move to LLVM provided by Vcpkg_
    * Download "Source code"
    * [Compile](https://llvm.org/docs/CMake.html#embedding-llvm-in-your-project) with required configuration (`Debug`, `Release`, etc.)
        * May require [CMake](https://cmake.org/download) to be installed separately
        * If building with Visual Studio, set `CMAKE_INSTALL_PATH` (if you need it) and build subproject called `INSTALL`
    * Add LLVM directory into system variable `Path`
        * It may look like `C:\Program Files (x86)\LLVM\bin`
* Open project folder from Visual Studio 2019
    * You may just run it with chosen configuration
    * Don't forget to setup command line arguments for debug
        * `.vs\launch.vs.json`
            * `{..."configurations": [...{..."args": "path/to/in.debug.slangir"...}...]...}`
        * Using GUI
            * Right-click on top `CMakeLists.txt`
            * "Debug and Launch Settings"

### MacOS

_Note_: this instructions assume presence of [Homebrew](https://brew.sh).

* [Homebrew](https://brew.sh/#install)
    * `brew install cmake`
    * `brew tap nlohmann/json`
    * `brew install nlohmann-json`
    * `brew install llvm@9`
* Build project
    * By hand
        * `mkdir bld && cd bld && cmake .. && make`
        * _**TODO**: check if LLVM is recognized properly_
    * Open using CLion or other IDE that supports CMake appropriately

## How to run project

`code_generator path/to/in.slangir`
