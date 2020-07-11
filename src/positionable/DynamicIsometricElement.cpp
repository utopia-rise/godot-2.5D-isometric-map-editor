#include <positionable/physics/DefaultStaticBody.h>
#include <DynamicIsometricElement.h>

using namespace godot;

void DynamicIsometricElement::_register_methods() {
    register_property("has_default_body", &DynamicIsometricElement::setHasDefaultBody,
            &DynamicIsometricElement::getHasDefaultBody, true);

    register_method("_init", &DynamicIsometricElement::_init);
    register_method("_enter_tree", &DynamicIsometricElement::_enter_tree);
    register_method("get_class", &DynamicIsometricElement::get_class);
    register_method("update_position_from_body", &DynamicIsometricElement::updatePositionFromBody);
    register_method("set_registered_body", &DynamicIsometricElement::setRegisteredBody);
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

PhysicsBody *DynamicIsometricElement::getRegisteredBody() const {
    return IsometricElement<DefaultKinematicBody>::getRegisteredBody();
}

void DynamicIsometricElement::setRegisteredBody(PhysicsBody *physicsBody) {
    IsometricElement<DefaultKinematicBody>::setRegisteredBody(physicsBody);
}

void DynamicIsometricElement::updatePositionFromBody(PhysicsBody *physicsBody) {
    IsometricElement<DefaultKinematicBody>::updatePositionFromBody(physicsBody);
}
