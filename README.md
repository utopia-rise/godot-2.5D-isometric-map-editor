# Godot 2.5D Isometric Map Editor

A Godot addon to create complex 2.5D Isometric Map.

Classic tiled map does not permit to create complex isometric map with 3D logic. This tool is designed so. Here
every basic node is an `IsometricPositionable`, which means it has 3D coordinated and size (an `AABB`). Then a
topological graph is generated so that tiles are well ordered, according to their 3D position.  
Here is a list of `IsometricPositionable`:
- `IsometricMap`, an `IsometricPositionable` designed to contains other `IsometricPositionable`.
- `IsometricTile`, basically a 3D bloc to create your map.
- `IsometricPlaceholder`, if you don't have assets you need yet, you still can design 2.5D Isometric with them.

All of those are Godot nodes. This means you can quickly derive from one, use a tile or a map in several maps, and 
change an element used in many maps without taking care of editing those maps. In other words, this tool is designed for
re-usability of assets and easy fix.

## Documentation

[1. Installation guide](.README/INSTALL.md)  
[2. User guide](.README/USER_GUIDE.md)  
[3. Compiling from sources](.README/COMPILING_FROM_SOURCES.md)  