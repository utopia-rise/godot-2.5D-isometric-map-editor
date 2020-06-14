#include <StaticIsometricElement.h>

using namespace godot;

StaticIsometricElement::StaticIsometricElement(): hasDefaultBody(true), defaultBody(nullptr) {

}

void StaticIsometricElement::_register_methods() {
    register_property("has_default_body", &StaticIsometricElement::setHasDefaultBody,
                      &StaticIsometricElement::getHasDefaultBody, true);
    register_property("slope_type", &StaticIsometricElement::setSlopeType, &StaticIsometricElement::getSlopeType,
                      static_cast<int>(SlopeType::NONE), GODOT_METHOD_RPC_MODE_DISABLED, GODOT_PROPERTY_USAGE_DEFAULT,
                      GODOT_PROPERTY_HINT_ENUM, "NONE,LEFT,RIGHT,FORWARD,BACKWARD");

    register_method("_enter_tree", &StaticIsometricElement::_enter_tree);
}

void StaticIsometricElement::_init() {
    IsometricPositionable::_init();
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

SlopeType
StaticIsometricElement::calculateSlopeOffset(Vector2 *slopeOffset, real_t tileWidthFloat, real_t tileHeightFloat,
                                       real_t width, real_t depth,
                                       real_t ratio) const {
    switch (slopeType) {
        case SlopeType::NONE:
            break;
        case SlopeType::LEFT:
            *slopeOffset = -Vector2(tileWidthFloat * 0.5f * width, tileHeightFloat * 0.5f * width) * ratio;
            break;
        case SlopeType::RIGHT:
            *slopeOffset = Vector2(tileWidthFloat * 0.5f * width, tileHeightFloat * 0.5f * width) * ratio;
            break;
        case SlopeType::FORWARD:
            *slopeOffset = -Vector2(-tileWidthFloat * 0.5f * depth, tileHeightFloat * 0.5f * depth) * ratio;
            break;
        case SlopeType::BACKWARD:
            *slopeOffset = Vector2(-tileWidthFloat * 0.5f * depth, tileHeightFloat * 0.5f * depth) * ratio;
            break;
    }
    return slopeType;
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

int StaticIsometricElement::getSlopeType() {
    return static_cast<int>(slopeType);
}

void StaticIsometricElement::setSlopeType(int type) {
    slopeType = (SlopeType) type;
    if (outlineDrawer) {
        setOutlineDrawer(outlineDrawer->getColor(), outlineDrawer->getLineSize());
    }
    update();
}
