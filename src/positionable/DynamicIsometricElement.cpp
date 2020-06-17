#include "DynamicIsometricElement.h"

using namespace godot;

void DynamicIsometricElement::_register_methods() {
    register_property("has_default_body", &DynamicIsometricElement::setHasDefaultBody,
            &DynamicIsometricElement::getHasDefaultBody, true);

    register_method("_init", &DynamicIsometricElement::_init);
    register_method("_enter_tree", &DynamicIsometricElement::_enter_tree);
}

void DynamicIsometricElement::_init() {
    IsometricPositionable::_init();
}

String DynamicIsometricElement::get_class() const {
    return "DynamicIsometricElement";
}
