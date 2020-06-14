//
// Created by piertho on 14/06/2020.
//

#include <DefaultStaticBody.h>
#include <gen/CollisionShape.hpp>
#include <positionable/IsometricPositionable.h>
#include <gen/BoxShape.hpp>

using namespace godot;

DefaultStaticBody::DefaultStaticBody(): collisionShape(nullptr) {

}

void DefaultStaticBody::_register_methods() {
    register_method("_init", &DefaultStaticBody::_init);
}

void DefaultStaticBody::_init() {

}

void DefaultStaticBody::updateCollisionShape(SlopeType slopeType, const Vector3 &size) {
    if (!collisionShape) {
        collisionShape = CollisionShape::_new();

        switch (slopeType) {
            case SlopeType::NONE: {
                BoxShape *shape = BoxShape::_new();
                shape->set_extents(size * 0.5);
                collisionShape->set_shape(shape);
            }
                break;
            case SlopeType::LEFT:
                break;
            case SlopeType::RIGHT:
                break;
            case SlopeType::FORWARD:
                break;
            case SlopeType::BACKWARD:
                break;
        }

        add_child(collisionShape);
        collisionShape->set_owner(this);
    }
}
