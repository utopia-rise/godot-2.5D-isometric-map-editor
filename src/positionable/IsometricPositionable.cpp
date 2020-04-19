#include "IsometricPositionable.h"
#include "../IsometricServer.h"

using namespace godot;

IsometricPositionable::IsometricPositionable() = default;

IsometricPositionable::~IsometricPositionable() = default;

void IsometricPositionable::_register_methods() {
    register_method("_enter_tree", &IsometricPositionable::_enter_tree);
    register_method("_exit_tree", &IsometricPositionable::_exit_tree);
    register_method("get_hexagone_coordinates", &IsometricPositionable::getHexagoneCoordinates);
    register_method("drawOutline", &IsometricPositionable::drawOutline);
    register_method("_on_resize", &IsometricPositionable::onResize);
    register_method("_grid_updated", &IsometricPositionable::gridUpdated);
    register_method("_on_select", &IsometricPositionable::onSelect);

    register_property("iso_position", &IsometricPositionable::isoPosition, Vector2());
    register_property("aabb", &IsometricPositionable::setAABB, &IsometricPositionable::getAABB, AABB(Vector3(), Vector3(1, 1, 1)));
}

void IsometricPositionable::_enter_tree() {
    zOrderSize = 1;
    updateZOrderSize(zOrderSize);
}

void IsometricPositionable::_exit_tree() {
    updateZOrderSize(-zOrderSize);
}

Transform2D IsometricPositionable::getHexagoneCoordinates() {
    auto orthoPosition = aabb.position;
    auto size = aabb.size;
    auto upperPoint = Vector3(orthoPosition.x, orthoPosition.y, orthoPosition.z + (float) IsometricServer::Z_RATIO * size.z);
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
    this->set_position(IsometricServer::getScreenCoordFrom3D(ab.position));
    isoPosition = get_position();
    onResize(ab.size);
}

int IsometricPositionable::getZOrderSize() {
    return zOrderSize;
}

void IsometricPositionable::setZOrderSize(int size) {
    int delta = size - zOrderSize;
    if (delta != 0) {
        updateZOrderSize(delta);
    }
    zOrderSize = size;
}

void IsometricPositionable::updateZOrderSize(int change) {
    auto parent = Object::cast_to<IsometricPositionable>(this->get_parent());
    if (parent) {
        parent->zOrderSize += change;
    }
}

void IsometricPositionable::onResize(godot::Vector3 size) {

}

void IsometricPositionable::gridUpdated(int stair) {

}

void IsometricPositionable::onSelect(bool isSelected) {

}
