#include <IsometricTile.h>

using namespace godot;

void IsometricTile::_register_methods() {
    register_method("_init", &IsometricTile::_init);
    register_method("get_class", &IsometricTile::get_class);
}

void IsometricTile::_init() {
    StaticIsometricElement::_init();
}

String IsometricTile::get_class() const {
    return "IsometricTile";
}