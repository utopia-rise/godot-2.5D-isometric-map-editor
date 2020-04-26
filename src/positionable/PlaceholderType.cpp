#include "PlaceholderType.h"

using namespace godot;

void PlaceholderType::_register_methods() {
    register_property("type_name", &PlaceholderType::setTypeName, &PlaceholderType::getTypeName, String("default"));
    register_property("color", &PlaceholderType::setColor, &PlaceholderType::getColor, Color( 0.83, 0.83, 0.83, 1 ));

    register_method("_init", &PlaceholderType::_init);
}

void PlaceholderType::_init() {
    typeName = "default";
    color = Color( 0.83, 0.83, 0.83, 1 );
}

String PlaceholderType::getTypeName() const {
    return typeName;
}

void PlaceholderType::setTypeName(String name) {
    typeName = name;
}

Color PlaceholderType::getColor() const {
    return color;
}

void PlaceholderType::setColor(Color col) {
    color = col;
}
