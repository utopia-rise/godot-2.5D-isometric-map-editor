#include <DefaultStaticBody.h>
#include <gen/CollisionShape.hpp>
#include <positionable/IsometricPositionable.h>
#include <gen/ConvexPolygonShape.hpp>

using namespace godot;

DefaultStaticBody::DefaultStaticBody(): collisionShape(nullptr) {

}

void DefaultStaticBody::_register_methods() {
    register_method("_init", &DefaultStaticBody::_init);
}

void DefaultStaticBody::_init() {

}

void DefaultStaticBody::updateCollisionShape(SlopeType slopeType, const Vector3 &size) {
    if (collisionShape) {
        remove_child(collisionShape);
        collisionShape->queue_free();
    }

    collisionShape = CollisionShape::_new();

    ConvexPolygonShape *shape = ConvexPolygonShape::_new();
    PoolVector3Array poolVector3Array;
    const Vector3 &originPoint {-0.5, -0.5, -0.5};
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