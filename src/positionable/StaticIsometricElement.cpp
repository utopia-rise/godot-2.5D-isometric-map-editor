#include <StaticIsometricElement.h>

using namespace godot;

StaticIsometricElement::StaticIsometricElement(): slopeType(SlopeType::NONE) {

}

void StaticIsometricElement::_register_methods() {
    register_property("slope_type", &StaticIsometricElement::setSlopeType, &StaticIsometricElement::getSlopeType,
                      static_cast<int>(SlopeType::NONE), GODOT_METHOD_RPC_MODE_DISABLED, GODOT_PROPERTY_USAGE_DEFAULT,
                      GODOT_PROPERTY_HINT_ENUM, "NONE,LEFT,RIGHT,FORWARD,BACKWARD");
    register_property("has_default_body", &StaticIsometricElement::setHasDefaultBody, &StaticIsometricElement::getHasDefaultBody,
                      true);

    register_method("_init", &StaticIsometricElement::_init);
    register_method("_enter_tree", &StaticIsometricElement::_enter_tree);
}

void StaticIsometricElement::_init() {
    IsometricPositionable::_init();
}

void StaticIsometricElement::_enter_tree() {
    IsometricElement<DefaultStaticBody>::_enter_tree();
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

int StaticIsometricElement::getSlopeType() const {
    return static_cast<int>(slopeType);
}

void StaticIsometricElement::setSlopeType(int type) {
    slopeType = (SlopeType) type;
    if (outlineDrawer) {
        setOutlineDrawer(outlineDrawer->getColor(), outlineDrawer->getLineSize());
    }
    hasMoved = true;
    update();
}

bool StaticIsometricElement::getHasDefaultBody() const {
    return IsometricElement<DefaultStaticBody>::getHasDefaultBody();
}

void StaticIsometricElement::setHasDefaultBody(bool b) {
    IsometricElement<DefaultStaticBody>::setHasDefaultBody(b);
}
