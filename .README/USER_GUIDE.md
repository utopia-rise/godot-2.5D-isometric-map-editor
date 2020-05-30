# User Guide

Welcome to the Godot 2.5D user guide. This is designed to describe how to use 2.5D Isometric Map editor.

# Editor commands

| Keybinding                     | Effect                                                                                                                                       |
|--------------------------------|----------------------------------------------------------------------------------------------------------------------------------------------|
| mouse left click               | Place an `IsometricPositionable` on the map if one is selected in selector. Otherwise, select `IsometricPositionable` at the click position. |
| Mouse left drag and drop       | Create a placeholder if it is selected in selector.                                                                                          |
| Ctrl + Z                       | Undo last action.                                                                                                                            |
| Ctrl + Y / Command + Shift + Z | Redo action.                                                                                                                                 |
| Z                              | Increase volume on Z axis for selected placeholder.                                                                                          |
| S                              | Decrease volume on Z axis for selected placeholder.                                                                                          |
| C                              | Change slope type of selected placeholder.                                                                                                   |
| E                              | Move edition grid of +1 on Z axis.                                                                                                           |
| D                              | Move edition grid of -1 on Z axis.                                                                                                           |
| BACKSPACE                      | Delete selected positionable.                                                                                                                |
| Ctrl + BACKSPACE               | Delete all positionable in map.                                                                                                              |
| O                              | Move positionable position of -1 on Y axis.                                                                                                  |
| Shift + O                      | Move positionable position of +1 on Z axis.                                                                                                  |
| L                              | Move positionable position of +1 on Y axis.                                                                                                  |
| Shift + L                      | Move positionable position of -1 on Z axis.                                                                                                  |
| K                              | Move positionable position of -1 on X axis.                                                                                                  |
| M                              | Move positionable position of +1 on X axis.                                                                                                  |
| V                              | Increase X size of edited map by adding from beginning (Element at (0, 0, 0) will then be at (1, 0, 0) after this operation).                |
| B                              | Increase Y size of edited map by adding from beginning (Element at (0, 0, 0) will then be at (0, 1, 0) after this operation).                |
| N                              | Increase Z size of edited map by adding from beginning (Element at (0, 0, 0) will then be at (0, 0, 1) after this operation).                |

# Cube unit dimensions

In this section we will deal with 2D screen dimensions of your engine cube meter *(a cube of size (1, 1, 1))*.

**TODO**

# Editor interface presentation

This section describe the different widget of edition windows.

## How to create root isometric node

Creating root isometric node is easy. This addon provides custom nodes, so first create a new scene and begin adding
root node by clicking on **custom node**:

![scene inspector]

Then you can type *isometric* to search for *isometric positionables*:

![scene choice]

Here you can choice either IsometricMap and isometricTile.

## Tile Edition Interface

IsometricTile is handled by editor to draw the dimensions of the tile, to help you place the elements in it.
The drawing is done according to the design specification of your game, set in `IsometricServer` singleton:
![isometric tile interface 0]
If you select the tile you can change tile dimensions:
![isometric tile interface 1]

## Map Edition Interface

Here is the Isometric map edition view:
![isometric map interface 0]
It is composed of the classic godot's scene inspector, scene editor and Node inspector *(in yellow)*.  
But the addon also provide an other inspector, that we call the **Isometric Positionable Inspector** *(in green)*.
This widget display available `IsometricTiles` and `IsometricMap`, according to the setup of your
`addons/IsometricMap/Config/path.json`. From their, you can select Tiles or Maps to design your maps.  
Note that placeholders can be created by selecting *placeholder* in tile section
of inspector.

As with IsometricTile inspector, when the `IsometricMap` node is selected you can change 3D size of the map.

As you can see, addon provides you a grid to represent your map per square meter. This is the edition grid we speak
about in [Editor Commands](#editor-commands). This is here you will add isometric positionables to your map.

# Starting design

In this section we will describe how to start creating 2.5D Isometric Maps.

## Designing Tiles

`IsometricTile` is a godot node. So it is as easy to design it as it is for other godot node, at the exception that you
will have to place the child `Sprite` in the cube drawn to help you position it:
![isometric tile design 0]

## Designing Maps

[scene inspector]: png/scene_inspector.png
[scene choice]: png/scene_choice.png
[isometric tile interface 0]: png/isometric_tile_interface_0.png
[isometric tile interface 1]: png/isometric_tile_interface_1.png
[isometric map interface 0]: png/isometric_map_interface_0.png
[isometric tile design 0]: gif/isometric-tile-design-0.gif