#include <DefaultKinematicBody.h>
#include <gen/CollisionShape.hpp>
#include <Input.hpp>
#include <KinematicCollision.hpp>

using namespace godot;

DefaultKinematicBody::DefaultKinematicBody(): speed(200) {

}

void DefaultKinematicBody::_register_methods() {
    register_method("_init", &DefaultKinematicBody::_init);
    register_method("_process", &DefaultKinematicBody::_process);
}

void DefaultKinematicBody::_init() {

}

void DefaultKinematicBody::_process(float delta) {
    if (parent) {
        if (parent->getHasMoved()) {
            const Vector3 &parentPosition = parent->getPosition3D();

            set_global_transform({
                {1, 0, 0, 0, 1, 0, 0, 0, 1},
                {parentPosition.x, parentPosition.z, parentPosition.y}
            });
            updateCollisionShapes();

            parent->setHasMoved(false);
        }

        Input *input = Input::get_singleton();

        Vector3 direction;

        if (input->is_action_pressed("player_goes_forward")) {
            direction += Vector3(0, -1, 0);
        }
        if (input->is_action_pressed("player_goes_backward")) {
            direction += Vector3(0, 1, 0);
        }
        if (input->is_action_pressed("player_goes_left")) {
            direction += Vector3(-1, 0, 0);
        }
        if (input->is_action_pressed("player_goes_right")) {
            direction += Vector3(1, 0, 0);
        }

        move_and_collide(direction * delta * speed);

        parent->setPosition3D(get_global_transform().origin);
    }
}

void DefaultKinematicBody::updateCollisionShapes() {
    if (collisionShape) {
        remove_child(collisionShape);
        collisionShape->queue_free();
    }

    calculateCollisionShape();

    add_child(collisionShape);
    collisionShape->set_owner(this);
}
