#include "IsometricPositionable.h"
#include "../IsometricServer.h"

using namespace godot;

IsometricPositionable::IsometricPositionable() : aabb({0, 0, 0}, {1, 1, 1}){

}


void IsometricPositionable::_register_methods() {
    register_method("_init", &IsometricPositionable::_init);
    register_method("_enter_tree", &IsometricPositionable::_enter_tree);
    register_method("_exit_tree", &IsometricPositionable::_exit_tree);
    register_method("get_class", &IsometricPositionable::get_class);
    register_method("get_hexagone_coordinates", &IsometricPositionable::getHexagoneCoordinates);
    register_method("drawOutline", &IsometricPositionable::drawOutline);
    register_method("get_aabb", &IsometricPositionable::getAABB);
    register_method("set_aabb", &IsometricPositionable::setAABB);
    register_method("_on_resize", &IsometricPositionable::_onResize);
    register_method("_on_grid_updated", &IsometricPositionable::_onGridUpdated);
    register_method("_on_select", &IsometricPositionable::_onSelect);

    register_property("iso_position", &IsometricPositionable::isoPosition, Vector2());
    register_property("position3d", &IsometricPositionable::setPosition3D, &IsometricPositionable::getPosition3D, Vector3());
    register_property("size3d", &IsometricPositionable::setSize3D, &IsometricPositionable::getSize3D, Vector3(1, 1, 1));
    register_property("is_temporary", &IsometricPositionable::setTemporary, &IsometricPositionable::isTemporary, true);
    register_property("debug_z", &IsometricPositionable::setDebugZ, &IsometricPositionable::getDebugZ, 0);
}

void IsometricPositionable::_init() {
    _onResize();
}

void IsometricPositionable::_enter_tree() {
    setZOrderSize(1);
    updateZOrderSize(zOrderSize);
}

void IsometricPositionable::_exit_tree() {
    updateZOrderSize(-zOrderSize);
}

String IsometricPositionable::get_class() const {
    return "IsometricPositionable";
}

Transform2D IsometricPositionable::getHexagoneCoordinates() const {
    const Vector3 &orthoPosition = aabb.position;
    const Vector3 &size = aabb.size;
    const Vector3 upperPoint(orthoPosition.x, orthoPosition.y, orthoPosition.z + (float) IsometricServer::getInstance().zRatio * size.z);
    const Vector3 lowerPoint(orthoPosition.x + size.x, orthoPosition.y + size.y, orthoPosition.z);
    const Vector3 leftPoint(orthoPosition.x, orthoPosition.y + size.y, orthoPosition.z);
    const Vector3 rightPoint(orthoPosition.x + size.x, orthoPosition.y, orthoPosition.z);
    real_t minX = upperPoint.x - upperPoint.z;
    real_t maxX = lowerPoint.x - lowerPoint.z;
    real_t minY = upperPoint.y - upperPoint.z;
    real_t maxY = lowerPoint.y - lowerPoint.z;
    real_t hMin = leftPoint.x - leftPoint.y;
    real_t hMax = rightPoint.x - rightPoint.y;
    return {minX, maxX, minY, maxY, hMin, hMax};
}

void IsometricPositionable::drawOutline() {
//    Upper Lines
    Color colorRed(255, 0, 0, 1);
    draw_line(upPoints[0], upPoints[1], colorRed, 10.0);
    draw_line(upPoints[1], upPoints[2], colorRed, 10.0);
    draw_line(upPoints[2], upPoints[3], colorRed, 10.0);
    draw_line(upPoints[3], upPoints[0], colorRed, 10.0);

//    Vertical Lines
    draw_line(upPoints[0], downPoints[0], colorRed, 10.0);
    draw_line(upPoints[1], downPoints[1], colorRed, 10.0);
    draw_line(upPoints[2], downPoints[2], colorRed, 10.0);
    draw_line(upPoints[3], downPoints[3], colorRed, 10.0);

//    Lower Lines
    draw_line(downPoints[0], downPoints[1], colorRed, 10.0);
    draw_line(downPoints[1], downPoints[2], colorRed, 10.0);
    draw_line(downPoints[2], downPoints[3], colorRed, 10.0);
    draw_line(downPoints[3], downPoints[0], colorRed, 10.0);
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

Vector3 IsometricPositionable::getPosition3D() const {
    return aabb.position;
}

void IsometricPositionable::setPosition3D(Vector3 pos) {
    aabb.position = pos;
    set_position(IsometricServer::getInstance().getScreenCoordFrom3D(pos));
    isoPosition = get_position();
}

Vector3 IsometricPositionable::getSize3D() const {
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

void IsometricPositionable::_onResize() {

}

void IsometricPositionable::_onGridUpdated(int stair) {

}

void IsometricPositionable::_onSelect(bool selected) {

}

bool IsometricPositionable::isTemporary() const {
    return temporary;
}

void IsometricPositionable::setTemporary(bool temp) {
    this->temporary = temp;
    update();
}

int IsometricPositionable::getDebugZ() const {
    return debugZ;
}

void IsometricPositionable::setDebugZ(int dZ) {
    this->debugZ = dZ;
}
