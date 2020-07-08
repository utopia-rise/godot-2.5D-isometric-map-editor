#include <DefaultKinematicBody.h>
#include <Input.hpp>
#include <KinematicCollision.hpp>
#include <gen/Engine.hpp>
#include <gen/RayShape.hpp>
#include <helpers/MathHelper.h>
#include <positionable/IsometricMap.h>

using namespace godot;

DefaultKinematicBody::DefaultKinematicBody(): speed(1), gravity(9.8), linearVelocity({0, 0, 0}) {

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
    initializeShapes();
}

void DefaultKinematicBody::_enter_tree() {
    if (parent) {
        const Vector3 &parentPosition { parent->getPosition3D() + parent->getPositionOffset() };
        const Vector3 &parentSize {parent->getSize3D()};

        set_global_transform({
            {1, 0, 0, 0, 1, 0, 0, 0, 1},
            {parentPosition.x, parentPosition.z, parentPosition.y}
        });
        collisionShape->set_global_transform({
            {1, 0, 0, 0, 1, 0, 0, 0, 1},
            {parentPosition.x + parentSize.x * 0.5f, parentPosition.z + 0.5f * parentSize.z, parentPosition.y + parentSize.y * 0.5f}
        });
        collisionShape->rotate_x(deg2rad(90));
        updateCollisionShapes();
    }
}

void DefaultKinematicBody::_physics_process(float delta) {
    if (parent) {
        if (parent->getHasMoved()) {
            const Vector3 &parentPosition { parent->getPosition3D() + parent->getPositionOffset() };
            const Vector3 &parentSize {parent->getSize3D()};

            set_global_transform({
                {1, 0, 0, 0, 1, 0, 0, 0, 1},
                {parentPosition.x, parentPosition.z, parentPosition.y}
            });
            collisionShape->set_global_transform({
                {1, 0, 0, 0, 1, 0, 0, 0, 1},
                {parentPosition.x + parentSize.x * 0.5f, parentPosition.z + 0.5f * parentSize.z, parentPosition.y + parentSize.y * 0.5f}
            });
            collisionShape->rotate_x(deg2rad(90));

            calculateCollisionShape();

            parent->setHasMoved(false);
            return;
        }

        if (!Engine::get_singleton()->is_editor_hint()) {
            Input *input = Input::get_singleton();

            linearVelocity += {0, -gravity * delta, 0};

            Vector3 horizontalVelocity;
            Vector3 verticalVelocity {0, linearVelocity.y, 0};

            if (input->is_action_pressed("player_goes_forward")) {
                horizontalVelocity += Vector3(-1, 0, -1).normalized() * speed;
            }
            if (input->is_action_pressed("player_goes_backward")) {
                horizontalVelocity += Vector3(1, 0, 1).normalized() * speed;
            }
            if (input->is_action_pressed("player_goes_left")) {
                horizontalVelocity += Vector3(-1, 0, 1).normalized() * speed;
            }
            if (input->is_action_pressed("player_goes_right")) {
                horizontalVelocity += Vector3(1, 0, -1).normalized() * speed;
            }

            linearVelocity = horizontalVelocity + verticalVelocity;

            linearVelocity = move_and_slide(linearVelocity, {0, 1, 0});

            parent->updatePositionFromBody(this);
        }
    }
}

void DefaultKinematicBody::calculateCollisionShape() {
    if (parent) {
        const Vector3 size{parent->getSize3D()};
        real_t radius = sqrt(static_cast<real_t>(size.x * size.x + size.y * size.y)) * 0.5f;
        real_t height = size.z - radius * 2;
        height = height < 0 ? 0 : height;
        shape->set_radius(radius);
        shape->set_height(height);
        collisionShape->set_shape(shape);
    }
}

void DefaultKinematicBody::updateCollisionShapes() {
    calculateCollisionShape();
    if (!collisionShape->get_parent()) {
        add_child(collisionShape);
    }
    collisionShape->set_owner(this);
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