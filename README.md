# Gremspo

A CLI game that is meant to be run on both Windows and Linux. It is my attempt at making a game that can run on CLI on both platforms, and can be built and run as easily as possible.

> Gremspo? wuzzat?

An anagram of `some-rpg` (without the dash).

## Building

### Windows

An `.sln` file is provided. Simply open the file using Visual Studio (project is made with VS2022) and build. No additional flags needed.

### Linux

**ENSURE THAT `libncurses-dev` IS INSTALLED**

A `CMakeLists.txt` is provided. As is (apparently) customary with other repositories: 
```sh 
mkdir build && cd build
cmake ..
make
```

