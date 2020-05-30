# User Guide

Welcome to the Godot 2.5D isometric map editor user guide. This is designed to describe how to use 2.5D Isometric Map
editor.

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
about in [Editor Commands](#editor-commands). This is here you will add isometric positionables to your map. The green
hilighting is to represent the position of your cursor in the 3D space of the map.

# Starting design

In this section we will describe how to start creating 2.5D Isometric Maps.

## Designing Tiles

`IsometricTile` is a godot node. So it is as easy to design it as it is for other godot node, at the exception that you
will have to place the child `Sprite` in the cube drawn to help you position it:
![isometric tile design 0]
As it is a Godot node, you can extends it to create more variant by adding children. You can add other sprites,
particles effects, sound, whatever node you want:
![isometric tile design 1]
So as you can see you can save a lot of time by thinking in a compositional way. Every modification on base will be
repercuted on nodes that inherits.

## Designing Maps

`IsometricMap` is an `IsometricPositionable` that act as an `IsometricPositionable` container. This means you can add
tiles in an `IsometricMap`, but also `IsometricMap`. This way you can use the same asset in several maps.  
Here is an example of usage: If you want to have the same house in two different maps, you can design the house as a map
and use it in the two map were it is needed.  
Note that there is no limit of depth. Meaning you can have a map, in a map, in a map, etc...

Also, `IsometricMap` is a Godot node. So same as `IsometricTile` you can inherit an `IsometricMap` to create variant.

Just keep in mind that this addon is a powerful tool to design by composition.

### Adding tiles to a map

To add tiles in a map, open the map you want to edit (or create one), and select your tile in
**Isometric Positionable Inspector**. Then you can place a tile by making a simple click, or add several by maintaining
left mouse button and moving the mouse:
![isometric map design 0]

### Adding map in maps

You can add maps in maps, and act by composition. To add a map do as describe with tiles, but having a map selected in
**Isometric Positionable Inspector**:
![isometric map design 1]

### Adding placeholder to a map

If you don't have the asset you need you still can use placeholders to start design your world. Select placeholder field
in **Isometric Positionable Inspector**, and then use drag and drop to set its dimensions. A single click will create a
(1, 1, 1) sized placeholder:
![isometric map design 2]
You can also increase a selected placeholder size on z axis by using **Z** key and decrease it by using **S** key:
![isometric map design 3]
Note that selecting is done by left click on a position that already contains a positionable.

You can also create types for placeholders. To do so, create a new resource, add PlaceholderType *gdns* to the resource
and change color and name. Then you can use this resource on a placeholder:
![isometric map design 5]

### Removing elements

You can remove positionable by selecting one and activate **backspace** key:
![isometric map design 4]
Note that activating **ctrl + backspace** will remove all positionable on map.

You can use **ctrl + z** and **ctrl + y** if you make a mistake.


[scene inspector]: png/scene_inspector.png
[scene choice]: png/scene_choice.png
[isometric tile interface 0]: png/isometric_tile_interface_0.png
[isometric tile interface 1]: png/isometric_tile_interface_1.png
[isometric map interface 0]: png/isometric_map_interface_0.png
[isometric tile design 0]: gif/isometric_tile_design_0.gif
[isometric tile design 1]: gif/isometric_tile_design_1.gif
[isometric map design 0]: gif/isometric_map_design_0.gif
[isometric map design 1]: gif/isometric_map_design_1.gif
[isometric map design 2]: gif/isometric_map_design_2.gif
[isometric map design 3]: gif/isometric_map_design_3.gif
[isometric map design 4]: gif/isometric_map_design_4.gif
[isometric map design 5]: gif/isometric_map_design_5.gif