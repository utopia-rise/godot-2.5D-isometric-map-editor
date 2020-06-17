#include "DynamicIsometricElement.h"

using namespace godot;

void DynamicIsometricElement::_register_methods() {
    register_method("_init", &DynamicIsometricElement::_init);
}

void DynamicIsometricElement::_init() {
    IsometricPositionable::_init();
}

String DynamicIsometricElement::get_class() const {
    return "DynamicIsometricElement";
}
