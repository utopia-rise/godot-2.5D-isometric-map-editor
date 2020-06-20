#include <DefaultKinematicBody.h>
#include <Input.hpp>
#include <KinematicCollision.hpp>
#include <gen/Engine.hpp>

using namespace godot;

DefaultKinematicBody::DefaultKinematicBody(): speed(1) {

}

void DefaultKinematicBody::_register_methods() {
    register_property("speed", &DefaultKinematicBody::setSpeed, &DefaultKinematicBody::getSpeed, 1.0f);

    register_method("_init", &DefaultKinematicBody::_init);
    register_method("_enter_tree", &DefaultKinematicBody::_enter_tree);
    register_method("_physics_process", &DefaultKinematicBody::_physics_process);
}

void DefaultKinematicBody::_init() {

}

void DefaultKinematicBody::_enter_tree() {
    initializeShapes();
    if (parent) {
        const Vector3 &parentPosition { parent->getPosition3D() };
        set_global_transform({
            {1, 0, 0, 0, 1, 0, 0, 0, 1},
            {parentPosition.x, parentPosition.z, parentPosition.y}
        });
        updateCollisionShapes();
    }
}

void DefaultKinematicBody::_physics_process(float delta) {
    if (parent) {
        if (parent->getHasMoved()) {
            const Vector3 &parentPosition { parent->getPosition3D() };

            set_global_transform({
                {1, 0, 0, 0, 1, 0, 0, 0, 1},
                {parentPosition.x, parentPosition.z, parentPosition.y}
            });

            calculateCollisionShape();

            parent->setHasMoved(false);
            return;
        }

        if (!Engine::get_singleton()->is_editor_hint()) {
            Input *input = Input::get_singleton();

            Vector3 direction;

            if (input->is_action_pressed("player_goes_forward")) {
                direction += Vector3(-1, 0, -1);
            }
            if (input->is_action_pressed("player_goes_backward")) {
                direction += Vector3(1, 0, 1);
            }
            if (input->is_action_pressed("player_goes_left")) {
                direction += Vector3(-1, 0, 1);
            }
            if (input->is_action_pressed("player_goes_right")) {
                direction += Vector3(1, 0, -1);
            }

            move_and_collide(direction * delta * speed);

            parent->updatePositionFromBody(this);
        }
    }
}

void DefaultKinematicBody::updateCollisionShapes() {
    calculateCollisionShape();
    add_child(collisionShape);
    collisionShape->set_owner(this);
}

float DefaultKinematicBody::getSpeed() const {
    return speed;
}

void DefaultKinematicBody::setSpeed(float s) {
    speed = s;
}