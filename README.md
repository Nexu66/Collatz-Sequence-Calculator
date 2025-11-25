# Collatz Sequence Calculator ⚙️🧮
Collatz Sequence Calculator — a small C++ / QtWidgets application that finds the number with the longest Collatz (3n + 1) sequence inside a user-specified interval, optionally using multiple threads to speed up the search.

## What it does ❔
Calculates, within a user-specified integer interval, which starting integer produces the longest Collatz sequence.
The GUI (Qt Widgets) lets you set an interval and the number of worker threads; the program searches the interval (optionally multi-threaded) and reports:
- Starting number that produced the longest chain
- Length of that chain
- Timing info
  
## ✨ Features

- 🖥️ Qt Widgets GUI — simple and responsive interface

- 🧵 Multithreaded calculation (user-configurable threads)

- ⏱️ Performance info: runtime measurements time info

- ✅ Unit tests with GoogleTest (tests/)

- 🛠️ CMake-based, cross-platform build (prefer Ninja generator)

- 🧭 Clean modular structure: src/app, src/core, src/controller, tests, etc.
## 🤖 Tech stack
- 💥 C++ (modern standard — project uses C++20 features)
- 🍃 Qt (Qt Widgets)
- 🔨 CMake — build system
- 🧪 GoogleTest — unit testing framework
## 🔧 Prerequisites
- C++ toolchain (g++, clang, or MSVC) that supports the project C++20 standard.
- CMake (>= 3.20).
- Qt development libraries (Qt6.5) with the Widgets module.
- git (to clone the repo).
- Ninja or your preferred generator (prefer Ninja).
## 🛠️ Quick build (CMake + Qt)
This is a generic cross-platform sequence that should work in most setups.
1. Clone the repo:
```bash
git clone https://github.com/Nexu66/Collatz-Sequence-Calculator.git
cd Collatz-Sequence-Calculator
```
2. Configure with CMake (example: out-of-source build).
For Unix:
```bash
mkdir build
cd build
cmake .. \
  -DCMAKE_BUILD_TYPE=Release \
  -DCMAKE_PREFIX_PATH="/path/to/Qt/lib/cmake"   # adjust to your Qt installation
```
For Windows:
```powershell
MD build
cd build
cmake .. -G "Visual Studio 17 2022" -A x64 -DCMAKE_PREFIX_PATH="C:\Path\To\Qt\lib\cmake"
```
3. Build. For Unix:
```bash
cmake --build .
```
For Windows:
```powershell
cmake --build . --config Release
```
4. Run
```bash
# Example (Linux/macOS)
./build/main

# Example (Windows)
.\build\Release\main.exe
```
## 🧪 Running tests (GoogleTest)
Build the tests target (they are discovered with gtest_discover_tests()):
```bash
cd build
cmake --build . --target tests
ctest -j$(nproc) -V
```
## 💡 Tips & notes
⚠️ cs_UpperLimitCap is large by default.
Allocating a huge static cache (e.g. 100M atomics) can blow memory — use smaller caps for development or refactor to a vector/sparse cache.

## 🧾 Project structure (high level)
A typical structure for this project is:
```bash
├── cmake
│   └── AddGoogleTest.cmake
├── CMakeLists.txt
├── src
│   ├── app
│   │   ├── CMakeLists.txt
│   │   └── main.cpp
│   ├── controller
│   │   ├── CMakeLists.txt
│   │   ├── controller.cpp
│   │   └── controller.hpp
│   ├── core
│   │   ├── CMakeLists.txt
│   │   ├── core.cpp
│   │   ├── core.hpp
│   │   ├── coreImpl
│   │   │   ├── CMakeLists.txt
│   │   │   ├── coreImpl.cpp
│   │   │   └── coreImpl.hpp
│   │   └── model
│   │       ├── CMakeLists.txt
│   │       └── model.hpp
│   ├── dialog
│   │   ├── CMakeLists.txt
│   │   ├── dialog.cpp
│   │   ├── dialog.hpp
│   │   ├── dialog.ui
│   │   └── view
│   │       ├── CMakeLists.txt
│   │       └── view.hpp
│   └── timer
│       ├── CMakeLists.txt
│       └── Timer.hpp
└── tests
    ├── CMakeLists.txt
    ├── reports
    └── test_coreImpl.cpp
```

