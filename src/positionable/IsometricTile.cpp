#include <IsometricTile.h>
#include "IsometricTile.h"

using namespace godot;

void IsometricTile::_register_methods() {
    register_method("_init", &IsometricTile::_init);
    register_method("get_class", &IsometricTile::get_class);
}

void IsometricTile::_init() {
    IsometricPositionable::_init();
}

godot::String godot::IsometricTile::get_class() const {
    return "IsometricTile";
}