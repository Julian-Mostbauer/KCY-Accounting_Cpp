# Building KCY-Accounting_Cpp (C++ Version)

This guide explains how to build the KCY-Accounting_Cpp project and run its unit tests.

## Prerequisites

- **C++17 compiler** (e.g., GCC, Clang)
- **CMake** (version 4.0 or higher)
- **Git** (to clone the repository)

## Clone the Repository

```sh
git clone https://github.com/Julian-Mostbauer/KCY-Accounting_Cpp.git
cd KCY-Accounting_Cpp
```

## Dependencies

### **Catch2** (Unit testing only)

The project uses a single-header version of Catch2, included in the `deps/` directory next to the project directory.
There you should have a `catch.hpp` and `catch.cpp`. If you want to run the unit tests you will need to download the
files from the [Catch2 repository](https://github.com/catchorg/Catch2/releases).

## Build the Project

Build the project using CMake. There are two executables: `license_server` and `license_tests`.
