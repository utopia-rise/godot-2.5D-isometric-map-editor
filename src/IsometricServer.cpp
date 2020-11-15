#include <IsometricServer.h>

using namespace godot;

IsometricServer::IsometricServer() : tileWidth(256), angle(30), topologicalMargin(0.0f) {
    tileHeight = calculateTileHeight();
    eZ = calculateEz();
    zRatio = eZ / static_cast<float>(tileHeight);
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
    tileHeight = calculateTileHeight();
    eZ = calculateEz();
}

int IsometricServer::getTileHeight() const {
    return tileHeight;
}

int IsometricServer::getAngle() const {
    return angle;
}

void IsometricServer::setAngle(int agl) {
    angle = agl;
    tileHeight = calculateTileHeight();
    eZ = calculateEz();
}

float IsometricServer::getEZ() const {
    return eZ;
}

double IsometricServer::getZRatio() const {
    return zRatio;
}

float IsometricServer::getTopologicalMargin() const {
    return topologicalMargin;
}

void IsometricServer::setTopologicalMargin(float margin){
    topologicalMargin = margin;
}


Vector3 IsometricServer::get3DCoordFromScreen(const Vector2 &pos, real_t orthZ) const {
    real_t isoX{pos.x};
    real_t isoY{pos.y};
    auto tileWidthFloat = static_cast<real_t>(tileWidth);
    auto tileHeightFloat = static_cast<real_t>(tileHeight);
    real_t orthX{isoX / tileWidthFloat + (isoY + orthZ * eZ) / tileHeightFloat};
    real_t orthY{(isoY + orthZ * eZ) / tileHeightFloat - isoX / tileWidthFloat};
    return {
            ::roundf(orthX),
            ::roundf(orthY),
            ::roundf(orthZ)
    };
}

Vector2 IsometricServer::getScreenCoordFrom3D(const Vector3 &pos) const {
    return {
            (pos.x - pos.y) * static_cast<real_t>(tileWidth) * 0.5f,
            (pos.x + pos.y) * static_cast<real_t>(tileHeight) * 0.5f - eZ * pos.z
    };
}

int IsometricServer::calculateTileHeight() const {
    return static_cast<int>(round(tileWidth * sin(deg2rad(static_cast<float>(angle)))));
}

float IsometricServer::calculateEz() const {
    return static_cast<float>((tileWidth / sqrt(2)) * cos(deg2rad(static_cast<float>(angle))));
}

bool IsometricServer::doHexagoneOverlap(const Transform2D &hex1, const Transform2D &hex2) {
    return !(hex1.get_axis(0).x >= hex2.get_axis(0).y || hex2.get_axis(0).x >= hex1.get_axis(0).y)
           && !(hex1.get_axis(1).x >= hex2.get_axis(1).y || hex2.get_axis(1).x >= hex1.get_axis(1).y)
           && !(hex1.get_origin().x >= hex2.get_origin().y || hex2.get_origin().x >= hex1.get_origin().y);
}

bool IsometricServer::isBoxInFront(const AABB &box, const AABB &other) {
    const Vector3 &boxEnd{box.position + box.size};
    const Vector3 &otherEnd{other.position + other.size};

    if (boxEnd.x - other.position.x <= topologicalMargin) {
        return false;
    } else if (otherEnd.x - box.position.x <= topologicalMargin) {
        return true;
    }

    if (boxEnd.y - other.position.y <= topologicalMargin) {
        return false;
    } else if (otherEnd.y - box.position.y <= topologicalMargin) {
        return true;
    }

    if (boxEnd.z - other.position.z <= topologicalMargin) {
        return false;
    } else if (otherEnd.z - box.position.z <= topologicalMargin) {
        return true;
    }

    const Vector3 &distance{box.position + boxEnd - other.position - otherEnd};
    const Vector3 &cameraVector{1, 1, zRatio};
    if (distance.dot(cameraVector) >= 0) {
        return true;
    }
    return false;

}
