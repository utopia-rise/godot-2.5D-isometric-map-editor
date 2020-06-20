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

}

void DefaultStaticBody::_enter_tree() {
    initializeShapes();
    updateCollisionShapes();
}

void DefaultStaticBody::_physics_process(float delta) {
    if (parent && parent->getHasMoved()) {
        const Vector3 &parentPosition {parent->getPosition3D()};
        set_global_transform({
            {1, 0, 0, 0, 1, 0, 0, 0, 1},
            {parentPosition.x, parentPosition.z, parentPosition.y}
        });
        calculateCollisionShape();
        parent->setHasMoved(false);
    }
}

void DefaultStaticBody::updateCollisionShapes() {
    calculateCollisionShape();
    add_child(collisionShape);
    collisionShape->set_owner(this);
}