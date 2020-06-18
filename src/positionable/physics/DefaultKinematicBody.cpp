#include <DefaultKinematicBody.h>
#include <gen/CollisionShape.hpp>
#include <Input.hpp>
#include <KinematicCollision.hpp>

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
    convexPolygonShape = ConvexPolygonShape::_new();
    shapeOwner = create_shape_owner(this);
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
        }

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

        const Vector3 &origin = get_global_transform().origin;
        parent->setPosition3D( {origin.x, origin.z, origin.y} );
    }
}

void DefaultKinematicBody::updateCollisionShapes() {
    calculateCollisionShape();
    shape_owner_add_shape(shapeOwner, convexPolygonShape);
}

float DefaultKinematicBody::getSpeed() {
    return speed;
}

void DefaultKinematicBody::setSpeed(float s) {
    speed = s;
}
