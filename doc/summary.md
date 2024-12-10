# MyDream - Raycasting Engine in C with SDL2

## General Overview

MyDream is a 3D engine project inspired by retro games like *Wolfenstein 3D*, developed in C using SDL2.

The engine employs the raycasting technique to create a 3D illusion from a 2D map by projecting rays and calculating distances to simulate depth.

## Project Architecture

### Core Engine

- Raycasting engine
- Math utilities (vectors, angles, distances)
- Main game loop
- Memory manager

### Graphics

- Rendering with SDL2
- Texture system
- Distance-based shading
- Minimap

### Physics

- Collision system
- Wall detection
- Movement handling

### Game Logic

- Player controls
- Game state management
- Level loading
- Configuration

### Tools (Optional)

- Level editor
- Visual debugger
- Profiling tools

## Technical Constraints

- **Performance**: Minimum of 60 FPS
- **Memory**: Efficient resource management
- **Code**: Modular and maintainable architecture