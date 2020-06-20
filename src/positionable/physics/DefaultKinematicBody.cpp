#include <DefaultKinematicBody.h>
#include <Input.hpp>
#include <KinematicCollision.hpp>
#include <gen/Engine.hpp>
#include <gen/RayShape.hpp>
#include <helpers/MathHelper.h>

using namespace godot;

DefaultKinematicBody::DefaultKinematicBody(): speed(1), gravity(9.8), rayCollisionShape(nullptr) {

}

void DefaultKinematicBody::_register_methods() {
    register_property("speed", &DefaultKinematicBody::setSpeed, &DefaultKinematicBody::getSpeed, 1.0f);
    register_property("gravity", &DefaultKinematicBody::setGravity, &DefaultKinematicBody::getGravity,
            9.8f);

    register_method("_init", &DefaultKinematicBody::_init);
    register_method("_enter_tree", &DefaultKinematicBody::_enter_tree);
    register_method("_physics_process", &DefaultKinematicBody::_physics_process);
}

void DefaultKinematicBody::_init() {
    rayCollisionShape = CollisionShape::_new();
}

void DefaultKinematicBody::_enter_tree() {
    initializeShapes();
    if (parent) {
        const Vector3 &parentPosition { parent->getPosition3D() };
        const Vector3 &parentSize {parent->getSize3D()};

        set_global_transform({
            {1, 0, 0, 0, 1, 0, 0, 0, 1},
            {parentPosition.x, parentPosition.z, parentPosition.y}
        });
        rayCollisionShape->set_global_transform({
            {1, 0, 0, 0, 1, 0, 0, 0, 1},
            {parentPosition.x + parentSize.x * 0.5f, parentPosition.z + 0.75f, parentPosition.y + parentSize.y * 0.5f}
        });
        rayCollisionShape->rotate_x(deg2rad(90));
        updateCollisionShapes();
    }
}

void DefaultKinematicBody::_physics_process(float delta) {
    if (parent) {
        if (parent->getHasMoved()) {
            const Vector3 &parentPosition { parent->getPosition3D() };
            const Vector3 &parentSize {parent->getSize3D()};

            set_global_transform({
                {1, 0, 0, 0, 1, 0, 0, 0, 1},
                {parentPosition.x, parentPosition.z, parentPosition.y}
            });
            rayCollisionShape->set_global_transform({
                {1, 0, 0, 0, 1, 0, 0, 0, 1},
                {parentPosition.x + parentSize.x * 0.5f, parentPosition.z + 0.75f, parentPosition.y + parentSize.y * 0.5f}
            });
            rayCollisionShape->rotate_x(deg2rad(90));

            prepareRayShape();
            calculateCollisionShape({0, 0.5, 0});

            parent->setHasMoved(false);
            return;
        }

        if (!Engine::get_singleton()->is_editor_hint()) {
            Input *input = Input::get_singleton();

            Vector3 direction {0, -gravity, 0};

            if (input->is_action_pressed("player_goes_forward")) {
                direction += Vector3(-1, 0, -1).normalized() * speed;
            }
            if (input->is_action_pressed("player_goes_backward")) {
                direction += Vector3(1, 0, 1).normalized() * speed;
            }
            if (input->is_action_pressed("player_goes_left")) {
                direction += Vector3(-1, 0, 1).normalized() * speed;
            }
            if (input->is_action_pressed("player_goes_right")) {
                direction += Vector3(1, 0, -1).normalized() * speed;
            }

            move_and_slide(direction);

            parent->updatePositionFromBody(this);
        }
    }
}

void DefaultKinematicBody::updateCollisionShapes() {
    prepareRayShape();
    calculateCollisionShape({0, 0.5, 0});
    add_child(collisionShape);
    add_child(rayCollisionShape);
    collisionShape->set_owner(this);
    rayCollisionShape->set_owner(this);
}

float DefaultKinematicBody::getSpeed() const {
    return speed;
}

void DefaultKinematicBody::setSpeed(float s) {
    speed = s;
}

float DefaultKinematicBody::getGravity() const {
    return gravity;
}

void DefaultKinematicBody::setGravity(float g) {
    gravity = g;
}

void DefaultKinematicBody::prepareRayShape() {
    RayShape *rayShape = RayShape::_new();
    rayShape->set_length(0.75);
    rayCollisionShape->set_shape(rayShape);
}
