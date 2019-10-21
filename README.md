# Systolic Simulator
## Presentation
Simulation of the flow of systolic algorithms; where computational units called "cell" are working on parallel, computing the result given by the last cell before feeding the result into the next one.

## Requirement
This project is done in “modern” C++ with CMake and hence required:
* A C++ compiler supporting **C++17**
* CMake version 3.4 or greater
* Make (if using UNIX)

## Usage
### Systolic library
The geneal usage of the Systolic Simulator is to decalare a new container of type `Systolic::Container` and to generate a predefined amount of cells, whose type and value are configurable by the user.

To simplify the creation of cells, the use of the `Systolic::CellArrayBuilder` can be used in conjonction with the board, to generate the instances of the cells from theit types and value.
Special cases are made for polynomial equations.

The Container can then be used to solves the equation either step by step, using the `step()` function or until completion using the `compute()` function.

Results and logs of the computations, partial or completed, can be queried using respectively `dumpOutputs()`, `getCurrentStateLog()` or `getLog()`.

Additional information about using the Systolic Simulator library can be found in the Doc folder.

### Main's CLI
The command line usage of the library is intended to be used for solving polynomial equation using the Horner's Rule.

For this end, the user must enter either all the coefficients of the operation in order using the `--coefs=` option or directly the equation using the `--equation=` option as well as the values of X using `--with-x=`.

The CLI offers the following options:
```
--with-x=(-)[0-9]+(,(-)[0-9]+, …)		: Defines the value of X, as an integer
--coefs=(-)[0-9]+(,(-)[0-9]+, …)		: Defines the coefficients of the equation, including 0 values, by their N order
--equation=Cn*X^N(+Cn-1*X^N-1+…)		: Single-variable polynomial equation
--verbose=[true|FALSE]					: Displays only the result on false (by default) or the complete log on true
--help									: Displays a help message
--about									: Display additional information about the program
```

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
```
cmake -G "Visual Studio 16 2019" -A x[64|86] ..
```
Or for previous releases:
```
`cmake -G "Visual Studio ?? 20?? [Win64"]
```

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
