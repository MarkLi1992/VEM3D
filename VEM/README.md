# README VEM                             
												     
This folder `VEM/` is about the whole C++ program.

This folder is composed of 4 subfolders:
* src
* Datafile
* Doxygen
* Output

## `src/`
`src` contains the header files and a Makefile. All the classes are 
template classes, so that there are no .cpp files except for the `main`.

### REQUIREMENTS FOR COMPILATION

* g++ version 4.8 or higher
* Eigen library installed in `/usr/local/include/`. Version 3.2.7 and 
3.2.9 tested.
  
### TO COMPILE AND RUN

To compile and run the program, it is sufficient to write the following 
commands, directly from the main folder `VEM/`:

```
make clean
make
./vem
```

Make sure that before running `./vem`, the wanted `datafile.dat` is 
written (see the following paragraph about the folder `Datafile/`.

## `Datafile/`

### DATAFILE - PARAMETERS TO SET

We provide a datafile to set the main parameters of the program without the need to 
recompile it.
We didn't use any library for it, but we implemented a simple parser in the main.cpp.
We used the C++ syntax for comments "//".

The Datafile `datafile.dat` is composed in 5 main sections:
* input files, in which the user chooses the `inputPoint` file (containing 
on each line the coordinates of every vertex point of the mesh) and the 
inputConnection file (containing on each line the index numbers of all 
points constituing an element);
* mesh type: it can be `ANYTHING2D`, `ANYTHING3D` OR `TETRAHEDRON`;
* the force term and solution functions;
* output files: it is advised to leave the output folder to Output/;
* typename: we can either choose `double` or `long double`.

If changes are restricted to these properties there is *no need to recompile the code*.
It is sufficient to change the datafile and then run again with `./vem`.
If the user wants to change the force term or solution functions he has to change the 
first lines of `main.cpp`, where there are all the functions, and then recompile.

## `Doxygen/`

We used Doxygen to provide the documentation.
To get it under the VEM folder run:

`doxygen Doxyfile`

The documentation will be produced in the Doxygen folder.

## `Output/`
All output files will be found there (if kept specified so). The different
output files are the following: 
* a file with the coordinates of the points corresponding to each vertex of the mesh;
* a file with the connections between vertices of the mesh;
* a file containing the errors in H^1 and L^\inf norms;
* a file with the solution.

The names of these files are determined by the user in `Datafile/datafile.dat`.











