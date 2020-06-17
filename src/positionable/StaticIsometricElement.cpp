#include <StaticIsometricElement.h>

using namespace godot;

StaticIsometricElement::StaticIsometricElement(): slopeType(SlopeType::NONE) {

}

void StaticIsometricElement::_register_methods() {
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

void StaticIsometricElement::setHasDefaultBody(bool b) {
    IsometricElement::setHasDefaultBody(b);
    if (is_inside_tree()) {
        updateDefaultBody();
    }
}

void StaticIsometricElement::updateDefaultBody() {
    if (hasDefaultBody) {
        if (!defaultBody) {
            defaultBody = DefaultStaticBody::_new();
            add_child(defaultBody);
            defaultBody->setParent(this);
            defaultBody->set_owner(this);
            hasMoved = true;
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
    hasMoved = true;
}

void StaticIsometricElement::setPosition3D(Vector3 pos) {
    IsometricPositionable::setPosition3D(pos);
    hasMoved = true;
}

int StaticIsometricElement::getSlopeType() const {
    return static_cast<int>(slopeType);
}

void StaticIsometricElement::setSlopeType(int type) {
    slopeType = (SlopeType) type;
    if (outlineDrawer) {
        setOutlineDrawer(outlineDrawer->getColor(), outlineDrawer->getLineSize());
    }
    if (defaultBody) {
        defaultBody->updateCollisionShape();
    }
    update();
}

void StaticIsometricElement::onResize() {
    IsometricPositionable::onResize();
    if (defaultBody) {
        defaultBody->updateCollisionShape();
    }
}
