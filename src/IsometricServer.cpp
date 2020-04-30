#include "IsometricServer.h"

using namespace godot;

IsometricServer::IsometricServer()
: tileWidth(256)
, tileHeight(128)
, angle(30) {
    eZ = calculateEz();
    zRatio = eZ / (float) tileHeight;
}

IsometricServer &IsometricServer::getInstance() {
    static IsometricServer instance;
    return instance;
}

int IsometricServer::getTileWidth() const {
    return tileWidth;
}

void IsometricServer::setTileWidth(int tW) {
    tileWidth = tW;
    //TODO calculate tileHeight
}

int IsometricServer::getTileHeight() const {
    return tileHeight;
    //TODO remove and calculate with angle and tileWidth
}

void IsometricServer::setTileHeight(int tH) {
    tileHeight = tH;
    //TODO remove and calculate with angle and tileWidth
}

int IsometricServer::getAngle() const {
    return angle;
}

void IsometricServer::setAngle(int agl) {
    angle = agl;
    eZ = calculateEz();
    //TODO calculate tileHeight
}

float IsometricServer::getEZ() const {
    return eZ;
}

double IsometricServer::getZRatio() const {
    return zRatio;
}

Vector3 IsometricServer::get3DCoordFromScreen(const Vector2 &pos, real_t orthZ) const {
    real_t isoX = pos.x;
    real_t isoY = pos.y;
    real_t orthX = isoX / (float) tileWidth + (isoY + orthZ * eZ) / (float) tileHeight;
    real_t orthY = (isoY + orthZ * eZ) / (float) tileHeight - isoX / (float) tileWidth;
    return {
            ::roundf(orthX),
            ::roundf(orthY),
            ::roundf(orthZ)
    };
}

Vector2 IsometricServer::getScreenCoordFrom3D(const Vector3 &pos) const {
    return {
            (pos.x - pos.y) * (real_t) tileWidth * 0.5f,
            (pos.x + pos.y) * (real_t) tileHeight * 0.5f - (real_t) (eZ * pos.z)
    };
}

float IsometricServer::calculateEz() const {
    return ((float) tileHeight / (float) sin(DEG2RAD((float) angle)) / (float) sqrt(2)) * (float) cos(DEG2RAD((float) angle));
}

bool IsometricServer::doHexagoneOverlap(const Transform2D &hex1, const Transform2D &hex2) {
    return !(hex1.get_axis(0).x >= hex2.get_axis(0).y || hex2.get_axis(0).x >= hex1.get_axis(0).y)
    && !(hex1.get_axis(1).x >= hex2.get_axis(1).y || hex2.get_axis(1).x >= hex1.get_axis(1).y)
    && !(hex1.get_origin().x >= hex2.get_origin().y || hex2.get_origin().x >= hex1.get_origin().y);
}

bool IsometricServer::isBoxInFront(const AABB &box, const AABB &other) {
    const Vector3 &boxEnd = box.position + box.size;
    const Vector3 &otherEnd = other.position + other.size;
    if (boxEnd.x <= other.position.x) {
        return false;
    } else if (otherEnd.x <= box.position.x) {
        return true;
    }

    if (boxEnd.y <= other.position.y) {
        return false;
    } else if (otherEnd.y <= box.position.y) {
        return true;
    }

    if (boxEnd.z <= other.position.z) {
        return false;
    } else if (otherEnd.z <= box.position.z) {
        return true;
    }
    return false;
}
