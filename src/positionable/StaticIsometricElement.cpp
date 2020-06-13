#include <StaticIsometricElement.h>
#include <gen/CollisionShape.hpp>
#include <gen/BoxShape.hpp>

using namespace godot;

StaticIsometricElement::StaticIsometricElement(): defaultBody(nullptr) {

}

void StaticIsometricElement::_register_methods() {
    register_property("has_default_body", &StaticIsometricElement::setDefaultBody,
            &StaticIsometricElement::hasDefaultBody, true);
}

void StaticIsometricElement::_init() {
    IsometricElement::_init();
}

String StaticIsometricElement::get_class() const {
    return "StaticIsometricElement";
}

bool StaticIsometricElement::hasDefaultBody() const {
    return defaultBody != nullptr;
}

void StaticIsometricElement::setDefaultBody(bool b) {
    if (b) {
        if (!defaultBody) {
            defaultBody = StaticBody::_new();
            CollisionShape *collisionShape = CollisionShape::_new();

            auto slopeType = static_cast<SlopeType>(getSlopeType());
            switch(slopeType) {
                case SlopeType::NONE: {
                    BoxShape *shape = BoxShape::_new();
                    shape->set_extents(getSize3D() * 0.5);
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

            const Vector3 &position = getPosition3D();
            defaultBody->global_translate({ position.x, position.z, position.y });
            defaultBody->add_child(collisionShape);
            add_child(defaultBody);
            collisionShape->set_owner(defaultBody);
            defaultBody->set_owner(this);
        }
    } else {
        if (defaultBody) {
            remove_child(defaultBody);
            defaultBody->queue_free();
            defaultBody = nullptr;
        }
    }
}
