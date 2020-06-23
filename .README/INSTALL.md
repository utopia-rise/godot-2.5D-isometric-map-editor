# Installation Guide

***/!\ Disclaimer:*** We currently have problems with installation of plugin. It seems to be a godot issue, see
[here](https://github.com/godotengine/godot/issues/38866) for further informations. A temporary workaround for this issue
can be found at the bottom of this installation guide.

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

## GDNS Inheritance Workaround

If you encounter the issue [above](https://github.com/godotengine/godot/issues/38866), the following manual steps should done
to allow the addon to function correctly. Please note this is temporary and should hopefully be resolved permanently at some
point in the future so users won't have to do this manual process.

After installing the addon using the steps above, find the `res://addons/IsometricMap/GdnsScripts/` directory and open each
`.gdns` file located within. This should bring up the file properties in the inspector. For each file, proceed to check,
and then uncheck, the `Singleton` property:  
![gdns workaround]

The end result will look the same as when you started - an unchecked box. However this will correctly populate and, more
importantly, save the `base` field in the `_global_script_classes` section in the `project.godot` file.

Save, restart Godot, and your project should now allow full use of the addon.

You can further verify the workaround has worked by opening up your `project.godot` file in an editor and checking each
IsometricMap gdns entry to ensure the `base` field is populated like so:  
```json
{
"base": "Node2D",
"class": "IsometricMap",
"language": "NativeScript",
"path": "res://addons/IsometricMap/GdnsScripts/positionable/IsometricMap.gdns"
}
```



[release addon]: ./png/release-addon.png
[addons folder]: ./png/addons-folder.png
[autoload isoserver]: ./png/autoload-isoserver.png
[activate addon]: ./png/activate-plugin.png
[gdns workaround]: ./png/gdns-workaround.png
