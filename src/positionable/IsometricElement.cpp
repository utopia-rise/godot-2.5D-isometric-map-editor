#include "IsometricElement.h"

using namespace godot;

IsometricElement::IsometricElement() : slopeType(SlopeType::NONE) {

}

void IsometricElement::_register_methods() {
    register_property("slope_type", &IsometricElement::setSlopeType, &IsometricElement::getSlopeType,
                      static_cast<int>(SlopeType::NONE), GODOT_METHOD_RPC_MODE_DISABLED, GODOT_PROPERTY_USAGE_DEFAULT,
                      GODOT_PROPERTY_HINT_ENUM, "NONE,LEFT,RIGHT,FORWARD,BACKWARD");

    register_method("get_class", &IsometricElement::get_class);
}

void IsometricElement::_init() {
    IsometricPositionable::_init();
}

String IsometricElement::get_class() const {
    return "IsometricElement";
}

SlopeType
IsometricElement::calculateSlopeOffset(Vector2 *slopeOffset, real_t tileWidthFloat, real_t tileHeightFloat,
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

int IsometricElement::getSlopeType() {
    return static_cast<int>(slopeType);
}

void IsometricElement::setSlopeType(int type) {
    slopeType = (SlopeType) type;
    if (outlineDrawer) {
        setOutlineDrawer();
    }
    update();
}
