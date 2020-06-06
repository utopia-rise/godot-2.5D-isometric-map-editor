# Installation Guide

***/!\ Disclaimer:*** We currently have problems with installation of plugin. It seems to be a godot issue, see
[here](https://github.com/godotengine/godot/issues/38866) for further informations.

This guide deals with installation of the addon in your project.

## Download a release

You can download addons.zip from [latest release](https://github.com/utopia-rise/godot-2.5D-isometric-map-editor/releases/latest), or
get it from the version you want in [release tab](https://github.com/utopia-rise/godot-2.5D-isometric-map-editor/releases):  
![release addon]

Extract this archive. You should get an `addons` folder that contains `IsometricMap` plugin:  
![addons folder]

## Install into your project

If you do not have any plugin already installed in your project, you can simply copy the extracted `addons` folder.  
If you already have installed plugin in you project, you should have an existing `addons` folder. You only have to copy
`IsometricMap` folder from extracted `addons.zip` in you project's `addons` folder.

### Maps and tiles path

First thing to do before opening project is to modify `addons/IsometricMap/Config/path.json`. It contains two paths:  
```json
{
    "tiles_path":"res://Scenes/examples/tiles",
    "maps_path":"res://Scenes/examples/maps"
}
```
Those paths represents the location (in your project) where you will store your *isometric maps* and your *isometric
tiles*. The choice is up to you, just don't store tiles and maps in same place.

### Isometric Server Singleton

Then you can open your project, which should tell you that the addon cannot find IsoServer singleton. This is because we
have to configure it.  
Head to `project settings`, `AutoLoad` tab and add `res://addons/IsometricMap/IsometricServer.tscn` with name
`IsoServer`:  
![autoload isoserver]

You can then activate `2.5D Isometric Map` addon int `Extensions` tab:  
![activate addon]

Isometric map addon is now installed on your project. You can now visit [user guide](./USER_GUIDE.md) to start design
your world !


[release addon]: ./png/release-addon.png
[addons folder]: ./png/addons-folder.png
[autoload isoserver]: ./png/autoload-isoserver.png
[activate addon]: ./png/activate-plugin.png