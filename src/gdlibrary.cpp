#include "positionable/IsometricPositionable.h"
#include "_IsometricServer.h"
#include "positionable/IsometricMap.h"
#include "positionable/IsometricTile.h"
#include "positionable/PlaceholderType.h"
#include "positionable/IsometricPlaceholder.h"

using namespace godot;

extern "C" void GDN_EXPORT iso_map_gdnative_init(godot_gdnative_init_options *o){
    Godot::gdnative_init(o);
}

extern "C" void GDN_EXPORT iso_map_gdnative_terminate(godot_gdnative_terminate_options *o){
    Godot::gdnative_terminate(o);
}

extern "C" void GDN_EXPORT iso_map_nativescript_init(void *handle){
    Godot::nativescript_init(handle);
    register_tool_class<IsometricPositionable>();
    register_tool_class<IsometricMap>();
    register_tool_class<IsometricTile>();
    register_tool_class<IsometricPlaceholder>();
    register_tool_class<PlaceholderType>();
    register_tool_class<_IsometricServer>();
}

