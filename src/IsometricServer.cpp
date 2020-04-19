#include "IsometricServer.h"

using namespace godot;

int IsometricServer::TILE_WIDTH = 256;
int IsometricServer::TILE_HEIGHT = 128;
int IsometricServer::ANGLE = 30;

int IsometricServer::E_Z = (int) ((TILE_HEIGHT / sin(DEG2RAD((float) ANGLE)) / sqrt(2)) * cos(DEG2RAD((float) ANGLE)));
int IsometricServer::Z_RATIO = IsometricServer::E_Z / TILE_HEIGHT;

int IsometricServer::getTileWidth() {
    return TILE_WIDTH;
}

void IsometricServer::setTileWidth(int tile_width) {
    TILE_WIDTH = tile_width;
    //TODO calculate TILE_HEIGHT
}

int IsometricServer::getTileHeight() {
    return TILE_HEIGHT;
    //TODO remove and calculate with ANGLE and TILE_WIDTH
}

void IsometricServer::setTileHeight(int tile_height) {
    tile_height = tile_height;
    //TODO remove and calculate with ANGLE and TILE_WIDTH
}

int IsometricServer::getAngle() {
    return ANGLE;
}

void IsometricServer::setAngle(int angle) {
    ANGLE = angle;
    calculateEz();
    //TODO calculate TILE_HEIGHT
}

Vector3 IsometricServer::get3DCoordFromScreen(Vector2 pos, real_t orthZ) {
    auto isoX = pos.x;
    auto isoY = pos.y;
    real_t orthX = isoX / (float) TILE_WIDTH + (isoY + orthZ * (float) E_Z) / (float) TILE_HEIGHT;
    real_t orthY = (isoY + orthZ * (float) E_Z) / (float) TILE_HEIGHT - isoX / (float) TILE_WIDTH;
    return {
            ::roundf(orthX),
            ::roundf(orthY),
            ::roundf(orthZ)
    };
}

Vector2 IsometricServer::getScreenCoordFrom3D(Vector3 pos) {
    return {
            (pos.x - pos.y) * (float) TILE_WIDTH * 0.5f,
            (pos.x + pos.y) * (float) TILE_HEIGHT * 0.5f
    };
}

int IsometricServer::calculateEz() {
    return (int) ((TILE_HEIGHT / sin(DEG2RAD((float) ANGLE)) / sqrt(2)) * cos(DEG2RAD((float) ANGLE)));
}

bool IsometricServer::doHexagoneOverlap(Transform2D hex1, Transform2D hex2) {
    return !(hex1.get_axis(0).x >= hex2.get_axis(0).y || hex2.get_axis(0).x >= hex1.get_axis(0).y)
    && !(hex1.get_axis(1).x >= hex2.get_axis(1).y || hex2.get_axis(1).x >= hex1.get_axis(1).y)
    && !(hex1.get_origin().x >= hex2.get_origin().y || hex2.get_origin().x >= hex1.get_origin().y);
}

bool IsometricServer::isBoxInFront(AABB box, AABB other) {
    Vector3 boxEnd = box.position + box.size;
    Vector3 otherEnd = other.position + other.size;
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
