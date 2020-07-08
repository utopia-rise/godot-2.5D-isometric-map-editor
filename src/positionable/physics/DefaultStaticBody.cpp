#include <DefaultStaticBody.h>
#include <gen/CollisionShape.hpp>
#include <positionable/IsometricPositionable.h>

using namespace godot;

void DefaultStaticBody::_register_methods() {
    register_method("_init", &DefaultStaticBody::_init);
    register_method("_enter_tree", &DefaultStaticBody::_enter_tree);
    register_method("_physics_process", &DefaultStaticBody::_physics_process);
}

void DefaultStaticBody::_init() {
    initializeShapes();
}

void DefaultStaticBody::_enter_tree() {
    updateCollisionShapes();
}

void DefaultStaticBody::_physics_process(float delta) {
    if (parent && parent->getHasMoved()) {
        const Vector3 &parentPosition {parent->getPosition3D() + parent->getPositionOffset()};
        set_global_transform({
            {1, 0, 0, 0, 1, 0, 0, 0, 1},
            {parentPosition.x, parentPosition.z, parentPosition.y}
        });
        calculateCollisionShape();
        parent->setHasMoved(false);
    }
}

void DefaultStaticBody::calculateCollisionShape() {
    auto slopeType = static_cast<SlopeType>(parent->getSlopeType());
    const Vector3 &size = parent->getSize3D();

    const Vector3 &convertedSize{size.x, size.z, size.y};
    PoolVector3Array poolVector3Array;
    Vector3 originPoint;
    poolVector3Array.push_back(originPoint);
    poolVector3Array.push_back({originPoint.x, originPoint.y, convertedSize.z});
    poolVector3Array.push_back({convertedSize.x, originPoint.y, originPoint.z});
    poolVector3Array.push_back({convertedSize.x,originPoint.y, convertedSize.z});

    switch (slopeType) {
        case SlopeType::NONE:
            poolVector3Array.push_back({originPoint.x, convertedSize.y, originPoint.z});
            poolVector3Array.push_back({originPoint.x, convertedSize.y, convertedSize.z});
            poolVector3Array.push_back({convertedSize.x, convertedSize.y, originPoint.z});
            poolVector3Array.push_back(convertedSize);
            break;
        case SlopeType::LEFT:
            poolVector3Array.push_back({originPoint.x, convertedSize.y, originPoint.z});
            poolVector3Array.push_back({originPoint.x, convertedSize.y, convertedSize.z});
            break;
        case SlopeType::RIGHT:
            poolVector3Array.push_back({convertedSize.x, convertedSize.y, originPoint.z});
            poolVector3Array.push_back(convertedSize);
            break;
        case SlopeType::FORWARD:
            poolVector3Array.push_back({originPoint.x, convertedSize.y, originPoint.z});
            poolVector3Array.push_back({convertedSize.x, convertedSize.y, originPoint.z});
            break;
        case SlopeType::BACKWARD:
            poolVector3Array.push_back({originPoint.x, convertedSize.y, convertedSize.z});
            poolVector3Array.push_back(convertedSize);
            break;
    }

    shape->set_points(poolVector3Array);
    collisionShape->set_shape(shape);
}

void DefaultStaticBody::updateCollisionShapes() {
    calculateCollisionShape();
    if (!collisionShape->get_parent()) {
        add_child(collisionShape);
    }
    collisionShape->set_owner(this);
}
