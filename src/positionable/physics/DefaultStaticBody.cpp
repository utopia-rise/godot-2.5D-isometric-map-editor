#include <DefaultStaticBody.h>
#include <gen/CollisionShape.hpp>
#include <positionable/IsometricPositionable.h>
#include <gen/BoxShape.hpp>
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
    if (!collisionShape) {
        collisionShape = CollisionShape::_new();

        Shape *shape = nullptr;
        switch (slopeType) {
            case SlopeType::NONE: {
                shape = BoxShape::_new();
                cast_to<BoxShape>(shape)->set_extents(size * 0.5);
            }
                break;
            case SlopeType::LEFT: {
                shape = ConvexPolygonShape::_new();
                PoolVector3Array poolVector3Array;
                const Vector3 &originPoint {-0.5, -0.5, -0.5};
                addBasePointsForSlope(poolVector3Array, size, originPoint);
                poolVector3Array.push_back(originPoint + Vector3(0, size.z, 0));
                poolVector3Array.push_back(originPoint + Vector3(0, size.z, size.y));
                cast_to<ConvexPolygonShape>(shape)->set_points(poolVector3Array);
            }
                break;
            case SlopeType::RIGHT: {
                shape = ConvexPolygonShape::_new();
                PoolVector3Array poolVector3Array;
                const Vector3 &originPoint {-0.5, -0.5, -0.5};
                addBasePointsForSlope(poolVector3Array, size, originPoint);
                poolVector3Array.push_back(originPoint + Vector3(size.x, size.z, 0));
                poolVector3Array.push_back(originPoint + Vector3(size.x, size.z, size.y));
                cast_to<ConvexPolygonShape>(shape)->set_points(poolVector3Array);
            }
                break;
            case SlopeType::FORWARD: {
                shape = ConvexPolygonShape::_new();
                PoolVector3Array poolVector3Array;
                const Vector3 &originPoint {-0.5, -0.5, -0.5};
                addBasePointsForSlope(poolVector3Array, size, originPoint);
                poolVector3Array.push_back(originPoint + Vector3(0, size.z, 0));
                poolVector3Array.push_back(originPoint + Vector3(size.x, size.z, 0));
                cast_to<ConvexPolygonShape>(shape)->set_points(poolVector3Array);
            }
                break;
            case SlopeType::BACKWARD: {
                shape = ConvexPolygonShape::_new();
                PoolVector3Array poolVector3Array;
                const Vector3 &originPoint {-0.5, -0.5, -0.5};
                addBasePointsForSlope(poolVector3Array, size, originPoint);
                poolVector3Array.push_back(originPoint + Vector3(0, size.z, size.y));
                poolVector3Array.push_back(originPoint + Vector3(size.x, size.z, size.y));
                cast_to<ConvexPolygonShape>(shape)->set_points(poolVector3Array);
            }
                break;
        }

        collisionShape->set_shape(shape);
        add_child(collisionShape);
        collisionShape->set_owner(this);
    }
}

void DefaultStaticBody::addBasePointsForSlope(PoolVector3Array &poolVector3Array, const Vector3 &size, const Vector3 &originPoint) {
    poolVector3Array.push_back(originPoint);
    poolVector3Array.push_back(originPoint + Vector3(0, 0, size.y));
    poolVector3Array.push_back(originPoint + Vector3(size.x, 0, 0));
    poolVector3Array.push_back(originPoint + Vector3(size.x, 0, size.y));
}
