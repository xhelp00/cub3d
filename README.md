# cub3d
You must create a “realistic” 3D graphical representation of the inside of a maze from a first-personpers pective. You have to create this representation using the Ray-Casting principles.
## Allowed functions
- open,close,read,write, printf,malloc,free,perror, strerror,exit 
- All functions of the math library(-lmmanman3math)
- All functions of the MinilibX / MLX42
- Libft
## General instructions
- a map in format *.cub
- The management of your window must remain smooth: changing to another window, minimizing, etc.
- Display different wall textures (the choice is yours) that vary depending on which side the wall is facing (North, South, East, West).
[cub3d.pdf](https://github.com/xhelp00/cub3d/files/12367418/cub3d.pdf)

## Study part / mad notes
- helpful video (raycaster in C using openGL/Glut) https://www.youtube.com/watch?v=gYRrGTC7GtA&list=LL&index=1&t=36s&ab_channel=3DSage
- //---------------------------Draw Rays and Walls--------------------------------
float distance(float ax, float ay, float bx, float by, float ang){ return cos(degToRad(ang))*(bx-ax)-sin(degToRad(ang))*(by-ay);}
mac compile flags:
- gcc tutorial.c -framework GLUT -Wno-deprecated-declarations -lglfw -framework Cocoa -framework OpenGL -framework IOKit 
