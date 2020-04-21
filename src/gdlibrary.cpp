#include "positionable/IsometricPositionable.h"
#include "_IsometricServer.h"
#include "positionable/IsometricMap.h"

using namespace godot;

extern "C" void GDN_EXPORT iso_map_gdnative_init(godot_gdnative_init_options *o){
    Godot::gdnative_init(o);
}

extern "C" void GDN_EXPORT iso_map_gdnative_terminate(godot_gdnative_terminate_options *o){
    Godot::gdnative_terminate(o);
}

extern "C" void GDN_EXPORT iso_map_nativescript_init(void *handle){
    Godot::nativescript_init(handle);
    register_class<IsometricPositionable>();
    register_class<_IsometricServer>();
    register_class<IsometricMap>();
}

