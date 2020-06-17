#include <DefaultStaticBody.h>
#include <gen/CollisionShape.hpp>
#include <positionable/IsometricPositionable.h>
#include <gen/ConvexPolygonShape.hpp>
#include <Area.hpp>

using namespace godot;

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
        updateCollisionShapes();

        parent->setHasMoved(false);
    }
}

void DefaultStaticBody::updateCollisionShapes() {
    if (collisionShape) {
        remove_child(collisionShape);
        collisionShape->queue_free();
    }

    calculateCollisionShape();

    add_child(collisionShape);
    collisionShape->set_owner(this);
}