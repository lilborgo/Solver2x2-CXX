# Solver2x2-CXX

A C++ solver for the 2x2 cube.

# Usage

First, you need to initialize the solver using:
```C++
    Solver2x2::init();
```
Or you can load from the memory usign:
```C++
    Solver2x2::loadFile("name.m2pc");
```
If the file does not exist, it will be created automatically. Event if the Solver is not initialized.
Its suggested to use always the loadFile, because its faster after the first time.

# Example

```C++
    Solver2x2::loadFile("sol.s2c");
    std::cout << Solver2x2::solve("RYWOGBOROYWBBYOWYBGRRGGW") << std::endl;
```
[example.cpp](example.cpp)

# Time and resources

This solver uses around 150 if you do not use the precomputed file, 30 if you use it.
The initialization requires around 3 seconds on an AMD Ryzen 5 3500U.
The solve (Solver2x2::solve) is immediatly instead, it is less than a millisecond.

# Compiling

```sh
cmake CMakeLists.txt
make
g++ -I include/ yourporgram.cpp -L. -lSolver2x2 -o yourporgram -Wl,-rpath,.
```