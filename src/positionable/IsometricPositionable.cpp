#include <IsometricPositionable.h>
#include <IsometricServer.h>
#include "IsometricPositionable.h"


using namespace godot;

IsometricPositionable::IsometricPositionable() : debugPoints(), aabb({0, 0, 0}, {1, 1, 1}),
zOrderSize(0), rendered(false), temporary(true), debugZ(0), outlineDrawer(nullptr) {

}


void IsometricPositionable::_register_methods() {
    register_method("_init", &IsometricPositionable::_init);
    register_method("_enter_tree", &IsometricPositionable::_enter_tree);
    register_method("_exit_tree", &IsometricPositionable::_exit_tree);
    register_method("get_class", &IsometricPositionable::get_class);
    register_method("get_hexagone_coordinates", &IsometricPositionable::getHexagoneCoordinates);
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
    const Vector3 &orthoPosition { aabb.position };
    const Vector3 &size { aabb.size };
    const Vector3 &upperPoint { Vector3(orthoPosition.x, orthoPosition.y, orthoPosition.z + IsometricServer::getInstance().zRatio * size.z) };
    const Vector3 &lowerPoint { Vector3(orthoPosition.x + size.x, orthoPosition.y + size.y, orthoPosition.z) };
    const Vector3 &leftPoint { Vector3(orthoPosition.x, orthoPosition.y + size.y, orthoPosition.z) };
    const Vector3 &rightPoint { Vector3(orthoPosition.x + size.x, orthoPosition.y, orthoPosition.z) };
    real_t minX = upperPoint.x - upperPoint.z;
    real_t maxX = lowerPoint.x - lowerPoint.z;
    real_t minY = upperPoint.y - upperPoint.z;
    real_t maxY = lowerPoint.y - lowerPoint.z;
    real_t hMin = leftPoint.x - leftPoint.y;
    real_t hMax = rightPoint.x - rightPoint.y;
    return {minX, maxX, minY, maxY, hMin, hMax};
}

void IsometricPositionable::preparePoints() {
    const Vector3 &size { getSize3D() };
    real_t w { size.x };
    real_t d { size.y };
    real_t h { size.z };

    int leftSlope { 0 };
    int rightSlope { 0 };
    int forwardSlope { 0 };
    int backwardSlope { 0 };

    int tileWidth { IsometricServer::getInstance().tileWidth };
    int tileHeight { IsometricServer::getInstance().tileHeight };

    Vector2 offset(0, static_cast<real_t>(-tileHeight) * 0.5f);

    float ratio { 0 };

    int debZ {getDebugZ() };

    if (h > 0) {
        ratio = static_cast<real_t>(debZ) / h;
    }

    auto tileWidthFloat = static_cast<real_t>(tileWidth);
    auto tileHeightFloat = static_cast<real_t>(tileHeight);
    Vector2 gridSlopeOffset;

    const SlopeType &slopeType { calculateSlopeOffset(&gridSlopeOffset, tileWidthFloat, tileHeightFloat, w, d, ratio) };
    switch (slopeType) {
        case SlopeType::NONE:
            break;
        case SlopeType::LEFT:
            leftSlope = 1;
            break;
        case SlopeType::RIGHT:
            rightSlope = 1;
            break;
        case SlopeType::FORWARD:
            forwardSlope = 1;
            break;
        case SlopeType::BACKWARD:
            backwardSlope = 1;
            break;
    }

    PoolVector2Array points;

    //Lower points
    points.push_back(Vector2(0, 0));
    points.push_back(Vector2(tileWidthFloat * 0.5f * w, tileHeightFloat * 0.5f * w));
    points.push_back(Vector2(tileWidthFloat * 0.5f * (w - d), tileHeightFloat * 0.5f * (d + w)));
    points.push_back(Vector2(-tileWidthFloat * 0.5f * d, tileHeightFloat * 0.5f * d));

    Vector2 heightOffset(0, - IsometricServer::getInstance().eZ * h);

    //Upper points
    points.push_back(points[0] + (1 - (rightSlope + backwardSlope)) * heightOffset);
    points.push_back(points[1] + (1 - (leftSlope + backwardSlope)) * heightOffset);
    points.push_back(points[2] + (1 - (leftSlope + forwardSlope)) * heightOffset);
    points.push_back(points[3] + (1 - (rightSlope + forwardSlope)) * heightOffset);

    upPoints.resize(0);
    upPoints.push_back(offset + points[4]);
    upPoints.push_back(offset + points[5]);
    upPoints.push_back(offset + points[6]);
    upPoints.push_back(offset + points[7]);

    leftPoints.resize(0);
    leftPoints.push_back(offset + points[2]);
    leftPoints.push_back(offset + points[3]);
    leftPoints.push_back(offset + points[7]);
    leftPoints.push_back(offset + points[6]);

    rightPoints.resize(0);
    rightPoints.push_back(offset + points[1]);
    rightPoints.push_back(offset + points[2]);
    rightPoints.push_back(offset + points[6]);
    rightPoints.push_back(offset + points[5]);

    downPoints.resize(0);
    downPoints.push_back(offset + points[0]);
    downPoints.push_back(offset + points[1]);
    downPoints.push_back(offset + points[2]);
    downPoints.push_back(offset + points[3]);

    if (debZ > -1) {
        Vector2 gridOffset(0, - IsometricServer::getInstance().eZ * static_cast<real_t>(debZ));
        debugPoints.resize(0);
        debugPoints.push_back(offset + points[0] + gridOffset + (rightSlope + backwardSlope) * gridSlopeOffset);
        debugPoints.push_back(offset + points[1] + gridOffset + (leftSlope + backwardSlope) * gridSlopeOffset);
        debugPoints.push_back(offset + points[2] + gridOffset + (leftSlope + forwardSlope) * gridSlopeOffset);
        debugPoints.push_back(offset + points[3] + gridOffset + (rightSlope + forwardSlope) * gridSlopeOffset);
    }
}

void IsometricPositionable::setOutlineDrawer() {
    preparePoints();
    if (outlineDrawer) {
        remove_child(outlineDrawer);
    }
    outlineDrawer = OutlineDrawer::_new();
    outlineDrawer->setPointsAndColor(&upPoints, &downPoints, Color(255, 0, 0, 1));
    add_child(outlineDrawer);
    outlineDrawer->update();
}

SlopeType
IsometricPositionable::calculateSlopeOffset(Vector2 *slopeOffset, real_t tileWidthFloat, real_t tileHeightFloat,
                                            real_t width, real_t depth,
                                            real_t ratio) const {
    return SlopeType::NONE;
}

AABB IsometricPositionable::getAABB() {
    return aabb;
}

void IsometricPositionable::setAABB(AABB ab) {
    aabb = ab;
    set_position(IsometricServer::getInstance().getScreenCoordFrom3D(ab.position));
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
    int delta { size - zOrderSize };
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
    auto *parent = Object::cast_to<IsometricPositionable>(this->get_parent());
    if (parent) {
        parent->zOrderSize += change;
    }
}

void IsometricPositionable::_onResize() {

}

void IsometricPositionable::_onGridUpdated(int stair) {

}

void IsometricPositionable::_onSelect(bool selected) {
    if (selected) {
        setOutlineDrawer();
    } else if (outlineDrawer) {
        remove_child(outlineDrawer);
        outlineDrawer = nullptr;
    }
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
