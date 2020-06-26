#include <IsometricPositionable.h>
#include <_IsometricServer.h>
#include <IsometricMap.h>
#include <IsometricTile.h>
#include <PlaceholderType.h>
#include <IsometricPlaceholder.h>
#include <positionable/StaticIsometricElement.h>
#include <positionable/physics/DefaultStaticBody.h>
#include <positionable/physics/DefaultKinematicBody.h>
#include <positionable/DynamicIsometricElement.h>

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
    register_tool_class<StaticIsometricElement>();
    register_tool_class<DynamicIsometricElement>();
    register_tool_class<IsometricMap>();
    register_tool_class<IsometricTile>();
    register_tool_class<IsometricPlaceholder>();
    register_tool_class<PlaceholderType>();
    register_tool_class<OutlineDrawer>();
    register_tool_class<DefaultStaticBody>();
    register_tool_class<DefaultKinematicBody>();
    register_tool_class<_IsometricServer>();
}

