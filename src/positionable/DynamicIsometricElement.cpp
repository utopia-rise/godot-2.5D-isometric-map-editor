#include <positionable/physics/DefaultStaticBody.h>
#include <DynamicIsometricElement.h>

using namespace godot;

void DynamicIsometricElement::_register_methods() {
    register_property("has_default_body", &DynamicIsometricElement::setHasDefaultBody,
            &DynamicIsometricElement::getHasDefaultBody, true);

    register_method("_init", &DynamicIsometricElement::_init);
    register_method("_enter_tree", &DynamicIsometricElement::_enter_tree);
    register_method("get_class", &DynamicIsometricElement::get_class);
}

void DynamicIsometricElement::_init() {
    IsometricPositionable::_init();
}

void DynamicIsometricElement::_enter_tree() {
    IsometricElement<DefaultKinematicBody>::_enter_tree();
}

String DynamicIsometricElement::get_class() const {
    return "DynamicIsometricElement";
}

bool DynamicIsometricElement::getHasDefaultBody() const {
    return IsometricElement<DefaultKinematicBody>::getHasDefaultBody();
}

void DynamicIsometricElement::setHasDefaultBody(bool b) {
    IsometricElement<DefaultKinematicBody>::setHasDefaultBody(b);
}
