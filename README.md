# Systolic Simulator
## Presentation
Simulation of the flow of systolic algorithms; where computational unit called "cell" are working on parallel, computing the result given by the last cell before feeding the result into the next one.

## Requirement
This project is done in "modern" C++ with CMake and hence required:
* A C++ compiler supporting **C++17**
* CMake version 3.1 or greater

## Usage
Instructions to come.

Basically, edit the `src/main.cpp` file to declare a cell container, fill it with the desired cells and inputs before computing the results.

## Compilation
### On UNIX
```
mkdir build && cd build && cmake .. && make
``
will create an executable named `systolic` at the root of the `build` folder.

### On Windows
Instructions to come.

## License
Every files of this repository is licensed under Apache License 2.0.

Please see the LICENSE file for further information.

## Credits
Régis BERTHELOT, 2019, as part of his master degree at the UVT.
