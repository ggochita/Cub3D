# Cub3D 🎮

Welcome to Cub3D!

Cub3D is a cool 3D game project inspired by classics like Wolfenstein 3D. It uses raycasting to turn a simple 2D map into a 3D world you can explore and have fun in. This project was built as part of the 42 curriculum and is written in C.


## What You Need 📦

Before you start, make sure you have these system libraries installed and using linux:

- **GCC:** C compiler.
- **X11 Libraries:**  
  - `libx11-dev`  
  - `libxext-dev`  
  - `libbsd-dev`  
  - Standard math library (`libm` is typically already included in your system)
- **Make:** To build the project easily.

### Installing Dependencies on Debian/Ubuntu 💻

Open your terminal and run:

```
sudo apt update
sudo apt install build-essential libx11-dev libxext-dev libbsd-dev
```

### Getting Started 🚀
To compile Cub3D, clone the repository and simply run:

```
make
```
This command builds all the source files and creates the executable (named cub3D).

### How to Play
Launch the game by running it with a map file:

```
./cub3D maps/good/[map_file.cub]
```

## Game Controls
- W / A / S / D: Move forward, left, backward, and right.
- Arrow Keys: Rotate your view.
- ESC: Exit the game.

## Notes

This project is built as a bare-bones version, just the minimum to get it running 😅. There's plenty of room to make it even cooler, so consider this a starting point.

