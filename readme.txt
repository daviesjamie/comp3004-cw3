COMP3004 COURSEWORK 3 - JAMIE DAVIES (JAGD1G11)

Control
=======
|-----------|---------------------------------------------------|
| Key       | Action                                            |
|-----------|---------------------------------------------------|
| Q, ESC    | Quit the program                                  |
| P         | Move camera to location screenshot was taken from |
| T         | Start the tour                                    |
| E         | End the tour                                      |
| LEFT      | Turn camera left                                  |
| RIGHT     | Turn camera right                                 |
| W         | Tilt camera up                                    |
| S         | Tilt camera down                                  |
| PAGE UP   | Raise camera                                      |
| PAGE DOWN | Lower camera                                      |
| UP        | Speed up camera                                   |
| DOWN      | Slow down camera                                  |
| SPACE     | Stop camera                                       |
| BACKSPACE | Reset camera position                             |
| .         | Print camera position to console                  |
| H, ?      | Print this help message                           |
|-----------|---------------------------------------------------|

The mouse is not used in this program.


List of Files
=============

asteroid.obj        - 3D model of an asteroid
Camera.cpp          - C++ class to control camera
Camera.hpp          - Header file for C++ camera class
clanger.obj         - 3D model of a clanger
credits.txt         - A list of the 3rd-party sources used
dustbinlid.obj      - 3D model of a bin-like lid
filetobuffer.cpp    - C++ function to load a file into a char buffer
filetobuffer.hpp    - Header file for C++ file loading function
fragment.glsl       - OpenGL fragment shader
hole.obj            - 3D model of a Clanger's hole
main.cpp            - The bulk of the C++ code for the project
Model.cpp           - A C++ class for the management of 3D resources
Model.hpp           - Header file for the C++ Model class
objloader.cpp       - C++ functions for loading a 3D .obj file
objloader.hpp       - Header file for the C++ .obj loader function
readme.txt          - This file.
screenshot.png      - A sample screenshot taken from the project.
shader.cpp          - C++ functions for loading and managing OpenGL shaders
shader.hpp          - Header file for the C++ shader functions
terrain2.obj        - 3D model of a moon-like landscape
vertex.glsl         - OpenGL vertex shader


Building
========

This program can be compiled in the usual way using GCC.

It depends on the GLFW3 and GLEW libraries.


How it works
============

The program works by loading in 3D objects from .obj files created in
Blender, applying transformations to them, and displaying them through
the use of OpenGL.
