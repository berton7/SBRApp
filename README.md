# SBRApp

This repo contains the CLI for controlling the self balancing robot hosted [here](https://github.com/berton7/Self-balancing-robot).

## Features
- [x] Cross-platform support (linux/Windows)
- [x] Xbox 360 controller support
- [ ] Bluetooth support

## Building

To get the application you can either download the pre-compiled package or build it yourself.
The building system is provided by cmake. Here are the platform-specific instructions:

### Linux

Create a build directory inside this folder and run cmake:
```
mkdir build
cd build/
cmake ..
```
This will configure the project. You can view and set all the options running `ccmake .`. Once done, compile everything with `make`.

## Windows
TODO
Use cmake-gui and visual studio.
