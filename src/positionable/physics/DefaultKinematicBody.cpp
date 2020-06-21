#include <DefaultKinematicBody.h>
#include <Input.hpp>
#include <KinematicCollision.hpp>
#include <gen/Engine.hpp>
#include <gen/RayShape.hpp>
#include <helpers/MathHelper.h>

using namespace godot;

DefaultKinematicBody::DefaultKinematicBody(): speed(1), gravity(98), rayCollisionShape(nullptr),
linearVelocity({0, 0, 0}) {

}

void DefaultKinematicBody::_register_methods() {
    register_property("speed", &DefaultKinematicBody::setSpeed, &DefaultKinematicBody::getSpeed, 1.0f);
    register_property("gravity", &DefaultKinematicBody::setGravity, &DefaultKinematicBody::getGravity,
            98.0f);

    register_method("_init", &DefaultKinematicBody::_init);
    register_method("_enter_tree", &DefaultKinematicBody::_enter_tree);
    register_method("_physics_process", &DefaultKinematicBody::_physics_process);
}

void DefaultKinematicBody::_init() {
    rayCollisionShape = CollisionShape::_new();
    initializeShapes();
}

void DefaultKinematicBody::_enter_tree() {
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
            collisionShape->set_global_transform({
                {1, 0, 0, 0, 1, 0, 0, 0, 1},
                {parentPosition.x + parentSize.x * 0.5f, parentPosition.z + 0.5f, parentPosition.y + parentSize.y * 0.5f}
            });
            rayCollisionShape->rotate_x(deg2rad(90));
            collisionShape->rotate_x(deg2rad(90));

            prepareRayShape();
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

            Godot::print(get_transform().origin);

            parent->updatePositionFromBody(this);
        }
    }
}

void DefaultKinematicBody::calculateCollisionShape() {
    shape->set_radius(0.2);
    shape->set_height(0.5);
    collisionShape->set_shape(shape);
}

void DefaultKinematicBody::updateCollisionShapes() {
    prepareRayShape();
    calculateCollisionShape();
    if (!collisionShape->get_parent()) {
        add_child(collisionShape);
    }
    if (!rayCollisionShape->get_parent()) {
        add_child(rayCollisionShape);
    }
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
