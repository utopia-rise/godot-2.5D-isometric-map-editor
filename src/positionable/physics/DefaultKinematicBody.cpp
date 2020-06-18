#include <DefaultKinematicBody.h>
#include <gen/CollisionShape.hpp>
#include <Input.hpp>
#include <KinematicCollision.hpp>

using namespace godot;

DefaultKinematicBody::DefaultKinematicBody(): speed(200) {

}

void DefaultKinematicBody::_register_methods() {
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
    calculateCollisionShape();
    shape_owner_add_shape(shapeOwner, convexPolygonShape);
}
