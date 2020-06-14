#include <StaticIsometricElement.h>

using namespace godot;

StaticIsometricElement::StaticIsometricElement(): hasDefaultBody(true), defaultBody(nullptr) {

}

void StaticIsometricElement::_register_methods() {
    register_property("has_default_body", &StaticIsometricElement::setHasDefaultBody,
                      &StaticIsometricElement::getHasDefaultBody, true);

    register_method("_enter_tree", &StaticIsometricElement::_enter_tree);
}

void StaticIsometricElement::_init() {
    IsometricElement::_init();
}

void StaticIsometricElement::_enter_tree() {
    IsometricPositionable::_enter_tree();
    const Array &children = get_children();
    if (hasDefaultBody) {
        for (int i = 0; i < children.size(); i++) {
            auto *defaultStaticBody = cast_to<DefaultStaticBody>(children[i]);
            if (defaultStaticBody) {
                defaultBody = defaultStaticBody;
                break;
            }
        }
    }
    updateDefaultBody();
}

String StaticIsometricElement::get_class() const {
    return "StaticIsometricElement";
}

bool StaticIsometricElement::getHasDefaultBody() const {
    return hasDefaultBody;
}

void StaticIsometricElement::setHasDefaultBody(bool b) {
    hasDefaultBody = b;
    if (is_inside_tree()) {
        updateDefaultBody();
    }
}

void StaticIsometricElement::updateDefaultBody() {
    if (hasDefaultBody) {
        if (!defaultBody) {
            defaultBody = DefaultStaticBody::_new();
            defaultBody->updateCollisionShape(static_cast<SlopeType>(getSlopeType()), getSize3D());
            add_child(defaultBody);
            const Vector3 &position = getPosition3D();
            defaultBody->set_global_transform({
                {1, 0, 0, 0, 1, 0, 0, 0, 1},
                {position.x, position.z, position.y}
            });
            defaultBody->set_owner(this);
        }
    } else {
        if (defaultBody) {
            remove_child(defaultBody);
            defaultBody->queue_free();
            defaultBody = nullptr;
        }
    }
}

void StaticIsometricElement::setAABB(AABB ab) {
    IsometricPositionable::setAABB(ab);
    if (is_inside_tree()) {
        const Vector3 &pos = ab.position;
        defaultBody->set_global_transform({
            {1, 0, 0, 0, 1, 0, 0, 0, 1},
            {pos.x, pos.z, pos.y}
        });
    }
}

void StaticIsometricElement::setPosition3D(Vector3 pos) {
    IsometricPositionable::setPosition3D(pos);
    if (is_inside_tree()) {
        defaultBody->set_global_transform({
            {1, 0, 0, 0, 1, 0, 0, 0, 1},
            {pos.x, pos.z, pos.y}
        });
    }
}
