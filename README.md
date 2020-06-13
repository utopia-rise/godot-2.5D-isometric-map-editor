# Godot 2.5D Isometric Map Editor (WIP)

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

*/!\Disclaimer* This project is still work in progress and not ready for production.

## Compatibility

### Operating Systems and platforms

This plugin is compatible with Windows, Linux, OSX (x64), android and ios (armv7 and armv8) for execution.  
You can use the editor tool on all desktop platforms (x64).

### Godot version

We support Godot 3.2.x versions.

## Documentation

[1. Installation guide](.README/INSTALL.md)  
[2. User guide](.README/USER_GUIDE.md)  
[3. Compiling from sources](.README/COMPILING_FROM_SOURCES.md)

## Authors

You can find authors in
[CONTRIBUTORS](https://github.com/utopia-rise/godot-2.5D-isometric-map-editor/graphs/contributors) section.

This project has first begun internally in Utopia-Rise as a proof of concept (gdscript based). Special thanks to the
team for testing this addon. It helped us to get from proof of concept to this beginning of more robust addon. Special
thanks to [CedNaru](https://github.com/CedNaru) for his active work on designing the tool and topological graph
generation.

Feel free to contribute and report bugs ! We're waiting for your issues and PR !

## Gifs
![isometric tile design 0] ![isometric tile design 1] ![isometric map design 0] ![isometric map design 1]


[isometric tile design 0]: .README/gif/isometric_tile_design_0.gif
[isometric tile design 1]: .README/gif/isometric_tile_design_1.gif
[isometric map design 0]: .README/gif/isometric_map_design_0.gif
[isometric map design 1]: .README/gif/isometric_map_design_1.gif
