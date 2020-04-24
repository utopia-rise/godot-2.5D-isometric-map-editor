#include "IsometricPositionable.h"
#include "../IsometricServer.h"

using namespace godot;

IsometricPositionable::IsometricPositionable() = default;

IsometricPositionable::~IsometricPositionable() = default;

void IsometricPositionable::_register_methods() {
    register_method("_init", &IsometricPositionable::_init);
    register_method("_enter_tree", &IsometricPositionable::_enter_tree);
    register_method("_exit_tree", &IsometricPositionable::_exit_tree);
    register_method("get_hexagone_coordinates", &IsometricPositionable::getHexagoneCoordinates);
    register_method("drawOutline", &IsometricPositionable::drawOutline);
    register_method("_on_resize", &IsometricPositionable::_onResize);
    register_method("_on_grid_updated", &IsometricPositionable::_onGridUpdated);
    register_method("_on_select", &IsometricPositionable::_onSelect);

    register_property("iso_position", &IsometricPositionable::isoPosition, Vector2());
    register_property("aabb", &IsometricPositionable::setAABB, &IsometricPositionable::getAABB, AABB(Vector3(), Vector3(1, 1, 1)));
    register_property("position3d", &IsometricPositionable::setPosition3D, &IsometricPositionable::getPosition3D, Vector3());
    register_property("size3d", &IsometricPositionable::setSize3D, &IsometricPositionable::getSize3D, Vector3(1, 1, 1));
}

void IsometricPositionable::_init() {
    aabb = AABB({0, 0, 0}, {1, 1, 1});
    _onResize();
}

void IsometricPositionable::_enter_tree() {
    setZOrderSize(1);
    updateZOrderSize(zOrderSize);
}

void IsometricPositionable::_exit_tree() {
    updateZOrderSize(-zOrderSize);
}

Transform2D IsometricPositionable::getHexagoneCoordinates() const {
    auto orthoPosition = aabb.position;
    auto size = aabb.size;
    auto upperPoint = Vector3(orthoPosition.x, orthoPosition.y, orthoPosition.z + (float) IsometricServer::getInstance().zRatio * size.z);
    auto lowerPoint = Vector3(orthoPosition.x + size.x, orthoPosition.y + size.y, orthoPosition.z);
    auto leftPoint = Vector3(orthoPosition.x, orthoPosition.y + size.y, orthoPosition.z);
    auto rightPoint = Vector3(orthoPosition.x + size.x, orthoPosition.y, orthoPosition.z);
    auto minX = upperPoint.x - upperPoint.z;
    auto maxX = lowerPoint.x - lowerPoint.z;
    auto minY = upperPoint.y - upperPoint.z;
    auto maxY = lowerPoint.y - lowerPoint.z;
    auto hMin = leftPoint.x - leftPoint.y;
    auto hMax = rightPoint.x - rightPoint.y;
    return {minX, maxX, minY, maxY, hMin, hMax};
}

void IsometricPositionable::drawOutline() {
//    Upper Lines
    const Color &colorRed = Color(255, 0, 0, 0);
    draw_line(upPoints[0], upPoints[1], colorRed, 2.0);
    draw_line(upPoints[1], upPoints[2], colorRed, 2.0);
    draw_line(upPoints[2], upPoints[3], colorRed, 2.0);
    draw_line(upPoints[3], upPoints[0], colorRed, 2.0);

//    Vertical Lines
    draw_line(upPoints[0], downPoints[0], colorRed, 1.0);
    draw_line(upPoints[1], downPoints[1], colorRed, 2.0);
    draw_line(upPoints[2], downPoints[2], colorRed, 2.0);
    draw_line(upPoints[3], downPoints[3], colorRed, 2.0);

//    Lower Lines
    draw_line(downPoints[0], downPoints[1], colorRed, 1.0);
    draw_line(downPoints[1], downPoints[2], colorRed, 2.0);
    draw_line(downPoints[2], downPoints[3], colorRed, 2.0);
    draw_line(downPoints[3], downPoints[0], colorRed, 1.0);
}

AABB IsometricPositionable::getAABB() {
    return aabb;
}

void IsometricPositionable::setAABB(AABB ab) {
    aabb = ab;
    this->set_position(IsometricServer::getInstance().getScreenCoordFrom3D(ab.position));
    isoPosition = get_position();
    _onResize();
}

Vector3 IsometricPositionable::getPosition3D() {
    return aabb.position;
}

void IsometricPositionable::setPosition3D(Vector3 pos) {
    aabb.position = pos;
    set_position(IsometricServer::getInstance().getScreenCoordFrom3D(pos));
    isoPosition = get_position();
}

Vector3 IsometricPositionable::getSize3D() {
    return aabb.size;
}

void IsometricPositionable::setSize3D(Vector3 s) {
    aabb.size = s;
    _onResize();
}

int IsometricPositionable::getZOrderSize() const {
    return zOrderSize;
}

void IsometricPositionable::setZOrderSize(int size) {
    int delta = size - zOrderSize;
    if (delta != 0) {
        updateZOrderSize(delta);
    }
    zOrderSize = size;
}

bool IsometricPositionable::isRendered() const {
    return rendered;
}

void IsometricPositionable::setRendered(bool isRendered) {
    this->rendered = isRendered;
}

void IsometricPositionable::updateZOrderSize(int change) {
    auto parent = Object::cast_to<IsometricPositionable>(this->get_parent());
    if (parent) {
        parent->zOrderSize += change;
    }
}

IsometricPositionable *IsometricPositionable::copy() {
    return IsometricPositionable::_new(this);
}

void IsometricPositionable::_onResize() {

}

void IsometricPositionable::_onGridUpdated(int stair) {

}

void IsometricPositionable::_onSelect(bool isSelected) {

}

bool IsometricPositionable::isTemporary() const {
    return temporary;
}

void IsometricPositionable::setTemporary(bool temp) {
    this->temporary = temp;
}

int IsometricPositionable::getDebugZ() const {
    return debugZ;
}

void IsometricPositionable::setDebugZ(int dZ) {
    this->debugZ = dZ;
}
