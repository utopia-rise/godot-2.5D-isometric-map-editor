#include "IsometricTile.h"

void godot::IsometricTile::_register_methods() {
    register_method("_init", &IsometricTile::_init);
    register_method("get_class", &IsometricTile::get_class);
}

void godot::IsometricTile::_init() {
    IsometricPositionable::_init();
}

godot::String godot::IsometricTile::get_class() const {
    return "IsometricTile";
}
