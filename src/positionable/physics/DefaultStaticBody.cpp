#include <DefaultStaticBody.h>
#include <gen/CollisionShape.hpp>
#include <positionable/IsometricPositionable.h>
#include <gen/ConvexPolygonShape.hpp>

using namespace godot;

DefaultStaticBody::DefaultStaticBody(): collisionShape(nullptr), parent(nullptr) {

}

void DefaultStaticBody::_register_methods() {
    register_method("_init", &DefaultStaticBody::_init);
    register_method("_process", &DefaultStaticBody::_process);
}

void DefaultStaticBody::_init() {

}

void DefaultStaticBody::_process(float delta) {
    if (parent->getHasMoved()) {
        const Vector3 &parentPosition = parent->getPosition3D();

        set_global_transform({
            {1, 0, 0, 0, 1, 0, 0, 0, 1},
            {parentPosition.x, parentPosition.z, parentPosition.y}
        });
        updateCollisionShape();

        parent->setHasMoved(false);
    }
}

void DefaultStaticBody::updateCollisionShape() {
    if (collisionShape) {
        remove_child(collisionShape);
        collisionShape->queue_free();
    }

    collisionShape = CollisionShape::_new();

    auto slopeType = static_cast<SlopeType>(parent->getSlopeType());
    const Vector3 &size = parent->getSize3D();

    ConvexPolygonShape *shape = ConvexPolygonShape::_new();
    PoolVector3Array poolVector3Array;
    Vector3 originPoint;
    poolVector3Array.push_back(originPoint);
    poolVector3Array.push_back(originPoint + Vector3(0, 0, size.y));
    poolVector3Array.push_back(originPoint + Vector3(size.x, 0, 0));
    poolVector3Array.push_back(originPoint + Vector3(size.x, 0, size.y));

    switch (slopeType) {
        case SlopeType::NONE:
            poolVector3Array.push_back(originPoint + Vector3(0, size.z, 0));
            poolVector3Array.push_back(originPoint + Vector3(0, size.z, size.y));
            poolVector3Array.push_back(originPoint + Vector3(size.x, size.z, 0));
            poolVector3Array.push_back(originPoint + Vector3(size.x, size.z, size.y));
            break;
        case SlopeType::LEFT:
            poolVector3Array.push_back(originPoint + Vector3(0, size.z, 0));
            poolVector3Array.push_back(originPoint + Vector3(0, size.z, size.y));
            break;
        case SlopeType::RIGHT:
            poolVector3Array.push_back(originPoint + Vector3(size.x, size.z, 0));
            poolVector3Array.push_back(originPoint + Vector3(size.x, size.z, size.y));
            break;
        case SlopeType::FORWARD:
            poolVector3Array.push_back(originPoint + Vector3(0, size.z, 0));
            poolVector3Array.push_back(originPoint + Vector3(size.x, size.z, 0));
            break;
        case SlopeType::BACKWARD:
            poolVector3Array.push_back(originPoint + Vector3(0, size.z, size.y));
            poolVector3Array.push_back(originPoint + Vector3(size.x, size.z, size.y));
            break;
    }

    shape->set_points(poolVector3Array);
    collisionShape->set_shape(shape);
    add_child(collisionShape);
    collisionShape->set_owner(this);
}

void DefaultStaticBody::setParent(IsometricElement<DefaultStaticBody> *staticIsometricElement) {
    parent = staticIsometricElement;
}
