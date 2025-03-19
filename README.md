# Cub3D

Welcome to Cub3D!  
Cub3D is a fun 3D game project inspired by classic titles like *Wolfenstein 3D*. Using raycasting, it transforms a simple 2D map into a 3D world that you can explore. This project is part of the 42 curriculum and is written in C.

## What You Need

Before you start, make sure you have these system libraries installed and using linux:

- **GCC:** C compiler.
- **X11 Libraries:**  
  - `libx11-dev`  
  - `libxext-dev`  
  - `libbsd-dev`  
  - Standard math library (`libm` is typically already included in your system)
- **Make:** To build the project easily.

### Installing Dependencies on Debian/Ubuntu

Open your terminal and run:

```
sudo apt update
sudo apt install build-essential libx11-dev libxext-dev libbsd-dev
```

### Getting Started
To compile Cub3D, clone the repository and simply run:

```
make
```
This command builds all the source files and creates the executable (named cub3D).

### How to Play
Launch the game by specifying a map file:

```
./cub3D maps/good/[map_file.cub]
```

## Game Controls
- W / A / S / D: Move forward, left, backward, and right.
- Arrow Keys: Rotate your view.
- ESC: Exit the game.
