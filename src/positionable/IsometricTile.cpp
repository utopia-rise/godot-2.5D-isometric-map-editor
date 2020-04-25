#include "IsometricTile.h"

void godot::IsometricTile::_init() {
    IsometricPositionable::_init();
}

void godot::IsometricTile::_register_methods() {
    register_method("_init", &IsometricTile::_init);
}
