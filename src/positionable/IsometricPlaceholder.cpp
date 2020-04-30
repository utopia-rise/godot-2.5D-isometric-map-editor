#include <gen/ResourceLoader.hpp>
#include "IsometricPlaceholder.h"
#include "../helpers/MathHelper.h"
#include "../IsometricServer.h"
#include <gen/Texture.hpp>

using namespace godot;

IsometricPlaceholder::IsometricPlaceholder(): debugPoints(), typeColor(0.83, 0.83, 0.83, 1) {

}

void IsometricPlaceholder::_register_methods() {
    register_property("placeholder_type", &IsometricPlaceholder::setPlaceholderType,
            &IsometricPlaceholder::getPlaceholderType,
            (Ref<PlaceholderType>) ResourceLoader::get_singleton()->load("res://addons/IsometricMap/prefab/types/default.tres"));
    register_property("slope_type", &IsometricPlaceholder::setSlopeType, &IsometricPlaceholder::getSlopeType,
            (int) SlopeType::NONE,GODOT_METHOD_RPC_MODE_DISABLED, GODOT_PROPERTY_USAGE_DEFAULT,
            GODOT_PROPERTY_HINT_ENUM, "NONE,LEFT,RIGHT,FORWARD,BACKWARD");

    register_method("_init", &IsometricPlaceholder::_init);
    register_method("_draw", &IsometricPlaceholder::_draw);
    register_method("get_class", &IsometricPlaceholder::get_class);
    register_method("_on_select", &IsometricPlaceholder::_onSelect);
}

void IsometricPlaceholder::_init() {
    IsometricPositionable::_init();
    updateColors();
}

void IsometricPlaceholder::_draw() {
    int debugZ = getDebugZ();
    if (debugZ == (int) getSize3D().z) {
        stairColor = PoolColorArray(Array::make(Color(1, 0.65, 0, 0.2)
                .linear_interpolate(downColor[0], 0.2)));
    } else if (debugZ == 0) {
        stairColor = PoolColorArray(Array::make(Color(0.63, 0.13, 0.94, 0.2)
                .linear_interpolate(downColor[0], 0.2)));
    } else {
        stairColor = PoolColorArray(Array::make(Color(1, 0, 0, 0.2)
                .linear_interpolate(downColor[0], 0.2)));
    }
    preparePoints();
    drawPoints();
}

String IsometricPlaceholder::get_class() const {
    return "IsometricPlaceholder";
}

void IsometricPlaceholder::preparePoints() {
    const Vector3 &size = getSize3D();
    int w = size.x;
    int d = size.y;
    int h = size.z;

    int leftSlope = 0;
    int rightSlope = 0;
    int forwardSlope = 0;
    int backwardSlope = 0;

    int tileWidth = IsometricServer::getInstance().tileWidth;
    int tileHeight = IsometricServer::getInstance().tileHeight;

    Vector2 offset(0, - tileHeight * 0.5);
    Vector2 gridSlopeOffset;

    float ratio = 0;

    int debugZ = getDebugZ();

    if (h > 0) {
        ratio = (float) debugZ / (float) h;
    }
    switch (slopeType) {
        case SlopeType::NONE:
            break;
        case SlopeType::LEFT:
            leftSlope = 1;
            upColor = sideSlopeColor;
            gridSlopeOffset = -Vector2(tileWidth * 0.5 * w, tileHeight * 0.5 * w) * ratio;
            break;
        case SlopeType::RIGHT:
            rightSlope = 1;
            upColor = sideSlopeColor;
            gridSlopeOffset = Vector2(tileWidth * 0.5 * w, tileHeight * 0.5 * w) * ratio;
            break;
        case SlopeType::FORWARD:
            forwardSlope = 1;
            upColor = forwardSlopeColor;
            gridSlopeOffset = -Vector2(-tileWidth * 0.5 * d, tileHeight * 0.5 * d) * ratio;
            break;
        case SlopeType::BACKWARD:
            backwardSlope = 1;
            upColor = backwardSlopeColor;
            gridSlopeOffset = Vector2(-tileWidth * 0.5 * d, tileHeight * 0.5 * d) * ratio;
            break;
    }

    PoolVector2Array points;

    //Lower points
    points.push_back(Vector2(0, 0));
    points.push_back(Vector2(tileWidth * 0.5 * w, tileHeight * 0.5 * w));
    points.push_back(Vector2(tileWidth * 0.5 * (w - d), tileHeight * 0.5 * (d + w)));
    points.push_back(Vector2(-tileWidth * 0.5 * d, tileHeight * 0.5 * d));

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

    if (debugZ > -1) {
        Vector2 gridOffset(0, - IsometricServer::getInstance().eZ * debugZ);
        debugPoints.resize(0);
        debugPoints.push_back(offset + points[0] + gridOffset + (rightSlope + backwardSlope) * gridSlopeOffset);
        debugPoints.push_back(offset + points[1] + gridOffset + (leftSlope + backwardSlope) * gridSlopeOffset);
        debugPoints.push_back(offset + points[2] + gridOffset + (leftSlope + forwardSlope) * gridSlopeOffset);
        debugPoints.push_back(offset + points[3] + gridOffset + (rightSlope + forwardSlope) * gridSlopeOffset);
    }
}

void IsometricPlaceholder::drawPoints() {
    const Vector3 &position3D = getPosition3D();
    const Vector3 &size = getSize3D();

    int debugZ = getDebugZ();

    if (isTemporary()) {
        Color upC = upColor[0];
        Color leC = leftColor[0];
        Color riC = rightColor[0];
        Color stairC = stairColor[0];
        upC.a = tempAlpha;
        leC.a = tempAlpha;
        riC.a = tempAlpha;
        stairC.a = tempAlpha;
        upColor.set(0, upC);
        leftColor.set(0, leC);
        rightColor.set(0, riC);
        stairColor.set(0, stairC);
    } else {
        Color upC = upColor[0];
        Color leC = leftColor[0];
        Color riC = rightColor[0];
        Color stairC = stairColor[0];
        upC.a = 1;
        leC.a = 1;
        riC.a = 1;
        stairC.a = 1;
        upColor.set(0, upC);
        leftColor.set(0, leC);
        rightColor.set(0, riC);
        stairColor.set(0, stairC);
        if (isSelected) {
            drawOutline();
        }
    }
    draw_polygon(upPoints, upColor);
    draw_polygon(leftPoints, leftColor);
    draw_polygon(rightPoints, rightColor);

    if (debugZ >= 0) {
        if (debugZ <= (int) size.z) {
            draw_polygon(debugPoints, stairColor);
            draw_line(debugPoints[0], debugPoints[1], stairColor[0], 2.0);
            draw_line(debugPoints[1], debugPoints[2], stairColor[0], 4.0);
            draw_line(debugPoints[2], debugPoints[3], stairColor[0], 4.0);
            draw_line(debugPoints[3], debugPoints[0], stairColor[0], 2.0);
        }
        real_t zRatio = IsometricServer::getInstance().zRatio;
        int tileWidth = IsometricServer::getInstance().tileWidth;
        int tileHeight = IsometricServer::getInstance().tileHeight;
        double eZ = IsometricServer::getInstance().eZ;

        int correctedZ = CLAMP(debugZ, 0, (int) size.z);
        int addedLines = CEIL(zRatio * correctedZ);

        int zDelta = debugZ - correctedZ;
        real_t offset = (zRatio - 1) * (real_t) zDelta;
        const Vector2 &base = downPoints[0] + Vector2(0, ((real_t) zDelta + offset) * (real_t) tileHeight - eZ * (real_t) debugZ);

        real_t maxX = mapSize.x - position3D.x - (real_t) zDelta - offset;
        real_t maxY = mapSize.y - position3D.y - (real_t) zDelta - offset;

        maxX = MIN(maxX, size.x + addedLines - 1);
        maxY = MIN(maxY, size.y + addedLines - 1);

        if (maxX > 0 && maxY > 0) {
            for (int i = 0; i < (int) (maxY + 1); i++) {
                const Vector2 &from = base + Vector2(tileWidth * 0.5 - i, tileHeight * 0.5 * i);
                const Vector2 &to = base + Vector2(tileWidth * 0.5 * (maxX - (real_t) i), tileHeight * 0.5 * (maxX + (real_t) i));
                draw_line(from, to, Color(0, 0, 0, 1), 2.0);
            }
            for (int i = 0; i < (int) (maxX + 1); i++) {
                const Vector2 &from = base + Vector2(tileWidth * 0.5 * i, tileHeight * 0.5 * i);
                const Vector2 &to = base + Vector2(tileWidth * 0.5 * ((real_t) i - maxY), tileHeight * 0.5 * (maxY + (real_t) i));
                draw_line(from, to, Color(0, 0, 0, 1), 2.0);
            }
        }
    }
}

void IsometricPlaceholder::updateColors() {
    leftColor = PoolColorArray(Array::make(typeColor.darkened(0.5)));
    rightColor = PoolColorArray(Array::make(typeColor.darkened(0.25)));
    upColor = PoolColorArray(Array::make(typeColor));
    downColor = PoolColorArray(Array::make(typeColor.darkened(0.9)));
    sideSlopeColor = PoolColorArray(Array::make(typeColor.darkened(0.10)));
    forwardSlopeColor = PoolColorArray(Array::make(typeColor.darkened(0.10)));
    backwardSlopeColor = PoolColorArray(Array::make(typeColor.lightened(0.10)));
}

void IsometricPlaceholder::setMapSize(const Vector3 &size) {
    mapSize = size;
}

void IsometricPlaceholder::_onGridUpdated(int stair) {
    setDebugZ(stair - (int) getPosition3D().z);
    update();
}

void IsometricPlaceholder::_onResize() {
    update();
}

void IsometricPlaceholder::_onSelect(bool selected) {
    isSelected = selected;
    update();
}

Ref<PlaceholderType> IsometricPlaceholder::getPlaceholderType() const {
    return placeholderType;
}

void IsometricPlaceholder::setPlaceholderType(Ref<PlaceholderType> pType) {
    placeholderType = pType;
    if (pType.ptr()) {
        typeColor = placeholderType->getColor();
        updateColors();
    }
}

int IsometricPlaceholder::getSlopeType() {
    return (int) slopeType;
}

void IsometricPlaceholder::setSlopeType(int type) {
    slopeType = (SlopeType) type;
    update();
}
