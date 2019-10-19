# Systolic Simulator
## Presentation
Simulation of the flow of systolic algorithms; where computational unit called "cell" are working on parallel, computing the result given by the last cell before feeding the result into the next one.

## Requirement
This project is done in "modern" C++ with CMake and hence required:
* A C++ compiler supporting **C++17**
* CMake version 3.4 or greater
* Make for UNIX

## Usage
(Instructions to come.)

The Systolic/* files can be used as a standalone library while main.cpp provide an example command line interface.
Look it up for an example for the time being.

## Compilation
### On UNIX
```
mkdir build && cd build && cmake .. && make
```
will create an executable named `systolic` at the root of the `build` folder.

### On Windows (using Visual Studio)
Using the Developer Command Prompt for Visual Studio:
First, create the folder:
```
mkdir build && cd build
```

Then, generate the project file:
For the latest Msvc in date:
`cmake -G "Visual Studio 16 2019" -A x[64|86] ..`
Or for previous releases:
`cmake -G "Visual Studio ?? 20?? [Win64"]`

Lastly, compile the program:
```
cmake --build . --target ALL_BUILD --config Release
```
A program named `systolic.exe` will now be present in the `build\Release` folder.

## License
Every files of this repository is licensed under Apache License 2.0.

Please see the LICENSE file for further information.

## Credits
Régis BERTHELOT, 2019, as part of his master degree at the UVT.
