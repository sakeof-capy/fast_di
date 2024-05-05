# fast_di

### Description
A small header-only library for building `C++20` apps based on Dependency Injection Container.

### Usage
Add the following line to `CMakeLists.txt` before adding this library as a subdirectory to enable static di:
```cmake
option(FAST_DI_ENABLE_GLOBAL_STATIC_DI "Enable Static Di" ON)
```
This might also need a complete recompilation of the project.