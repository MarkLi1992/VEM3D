# README CONVERGENCE

This file is about the content of the `Convergence/` folder, where the 
convergence of the a priori error on rectangular/cubic meshes, respectively 
in 2D and in 3D, is done. To do this numerical error analysis, some particular 
Laplace equation with homogeneous boundary conditions are solved on domains 
(0,1)^d, where d=2 in 2D or d=3 in 3D. 

This folder contains five main subfolders, `MeshSquare2D`, `MeshSquare3D`, `MeshSphere3D`, 
`OutputSquare` and `OutputSphere`, together with two Matlab scripts `cvPlot` and `cvPlotSphere` 
and some result plots.

## `MeshSquare2D/`
This folder contains the files generated by the scripts in the `Python/` folder 
that contain the information on the 2D square meshes used to perform the 
convergence analysis.

## `MeshSquare3D/`
This folder contains the files generated by the scripts in the `Python/` folder 
that contain the information on the 3D cubed meshes used to perform the convergence analysis.
Only two files are missing, called `point-128.txt` and `conn-128.txt` because 
they are too heavy to be hosted on Github. They can thus be found [here](https://drive.google.com/open?id=0B5q8XwMR3eamM0ZIVXhHdG16UE0) 
and they should be added to this folder to make the script `cvPlot.m` work.

## `OutputSquare/`
This folder contains the output files of `./vem`, containing the solutions 
and the error files.

## `MeshSphere3D/`
This folder contains the files generated by the scripts in the `Python/` folder 
that contain the information on the 3D tetrahedron meshes of a 3D sphere, 
used to perform the convergence analysis.

## `cvPlot.m`
This scipt is used to plot the graphs `convergencePlot2D` and `convergencePlot3D` 
where the absolute a priori H^1 error is plotted with respect to the mesh size h 
when solving the problem on a 2D square/3D cube.
Moreover, in the script is computed algebraically the convergence order 
of the error under h-refinement.

## `cvPlotSphere.m`
This scipt is used to plot the graph `convergenceSpherePlot3D` where the 
absolute a priori H^1 error is plotted with respect to the mesh size h when 
solving the problem on the 3D sphere (see exact equations in this file).
Moreover, in the script is computed algebraically the convergence order 
of the error under h-refinement.




