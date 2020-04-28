#include "IsometricTile.h"

void godot::IsometricTile::_register_methods() {
    register_method("_init", &IsometricTile::_init);
    register_method("get_class", &IsometricTile::getClass);
}

void godot::IsometricTile::_init() {
    IsometricPositionable::_init();
}

godot::String godot::IsometricTile::getClass() const {
    return "IsometricTile";
}
