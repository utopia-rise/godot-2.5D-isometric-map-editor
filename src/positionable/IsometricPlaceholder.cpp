#include <gen/ResourceLoader.hpp>
#include "IsometricPlaceholder.h"
#include "../helpers/MathHelper.h"
#include "../IsometricServer.h"
#include <gen/Texture.hpp>

using namespace godot;

void IsometricPlaceholder::_register_methods() {
    register_property("placeholder_type", &IsometricPlaceholder::setPlaceholderType,
            &IsometricPlaceholder::getPlaceholderType,
                      (PlaceholderType *) ResourceLoader::get_singleton()->load("res://addons/IsometricMap/prefab/types/default.tres").ptr());
    register_property("slope_type", &IsometricPlaceholder::setSlopeType, &IsometricPlaceholder::getSlopeType,
            (int) SlopeType::NONE,GODOT_METHOD_RPC_MODE_DISABLED, GODOT_PROPERTY_USAGE_DEFAULT,
            GODOT_PROPERTY_HINT_ENUM, "NONE,LEFT,RIGHT,FORWARD,BACKWARD");

    register_method("_init", &IsometricPlaceholder::_init);
    register_method("_draw", &IsometricPlaceholder::_draw);
}

void IsometricPlaceholder::_init() {
    IsometricPositionable::_init();
    placeholderType = (PlaceholderType *) ResourceLoader::get_singleton()->load("res://addons/IsometricMap/prefab/types/default.tres").ptr();
    updateColors();
}

void IsometricPlaceholder::_draw() {
    int debugZ = getDebugZ();
    if (debugZ == (int) getAABB().size.z) {
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

    Vector2 offset = Vector2(0, - tileHeight * 0.5);
    Vector2 gridSlopeOffset = Vector2();

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

    PoolVector2Array points = PoolVector2Array();

    //Lower points
    points.push_back(Vector2(0, 0));
    points.push_back(Vector2(tileWidth * 0.5 * w, tileHeight * 0.5 * w));
    points.push_back(Vector2(tileWidth * 0.5 * (w - d), tileHeight * 0.5 * (d + w)));
    points.push_back(Vector2(-tileWidth * 0.5 * d, tileHeight * 0.5 * d));

    Vector2 heightOffset = Vector2(0, - IsometricServer::getInstance().eZ * h);

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
        Vector2 gridOffset = Vector2(0, - IsometricServer::getInstance().eZ * debugZ);
        debugPoints.resize(0);
        debugPoints.push_back(offset + points[0] + gridOffset + (rightSlope + backwardSlope) * gridSlopeOffset);
        debugPoints.push_back(offset + points[1] + gridOffset + (leftSlope + backwardSlope) * gridSlopeOffset);
        debugPoints.push_back(offset + points[2] + gridOffset + (leftSlope + forwardSlope) * gridSlopeOffset);
        debugPoints.push_back(offset + points[3] + gridOffset + (rightSlope + forwardSlope) * gridSlopeOffset);
    }
}

void IsometricPlaceholder::drawPoints() {
    draw_polygon(upPoints, upColor);
    draw_polygon(leftPoints, leftColor);
    draw_polygon(rightPoints, rightColor);

    Vector3 position3D = getPosition3D();
    Vector3 size = getSize3D();

    int debugZ = getDebugZ();
    if (debugZ > -1) {
        real_t zRatio = IsometricServer::getInstance().zRatio;
        int tileWidth = IsometricServer::getInstance().tileWidth;
        int tileHeight = IsometricServer::getInstance().tileHeight;

        int correctedZ = CLAMP(debugZ, 0, (int) size.z);
        int addedLines = CEIL(zRatio * correctedZ);

        int zDelta = debugZ - correctedZ;
        real_t offset = (zRatio - 1) * (real_t) zDelta;
        Vector2 base = downPoints[0] + Vector2(0, ((real_t) zDelta + offset) * (real_t) tileHeight - (real_t) tileHeight * (real_t) debugZ);

        real_t maxX = mapSize.x - position3D.x - (real_t) zDelta - offset;
        real_t maxY = mapSize.y - position3D.y - (real_t) zDelta - offset;

        maxX = MIN(maxX, size.x + addedLines - 1);
        maxY = MIN(maxY, size.y + addedLines - 1);

        if (maxX > 0 && maxY > 0) {
            for (int i = 0; i < (int) (maxY + 1); i++) {
                Vector2 from = base + Vector2(tileWidth * 0.5 - i, tileHeight * 0.5 * i);
                Vector2 to = base + Vector2(tileWidth * 0.5 * (maxX - (real_t) i), tileHeight * 0.5 * (maxX + (real_t) i));
                draw_line(from, to, Color(0, 0, 0, 1), 2.0);
            }
            for (int i = 0; i < (int) (maxX + 1); i++) {
                Vector2 from = base + Vector2(tileWidth * 0.5 * i, tileHeight * 0.5 * i);
                Vector2 to = base + Vector2(tileWidth * 0.5 * ((real_t) i - maxY), tileHeight * 0.5 * (maxY + (real_t) i));
                draw_line(from, to, Color(0, 0, 0, 1), 2.0);
            }
        }
        if ((real_t) debugZ <= size.z) {
            draw_polygon(debugPoints, Array::make(stairColor));
            Color stairC = stairColor[0];
            stairC.a = 1;
            stairColor.set(0, stairC);
            draw_line(debugPoints[0], debugPoints[1], stairColor[0], 2.0);
            draw_line(debugPoints[1], debugPoints[2], stairColor[0], 4.0);
            draw_line(debugPoints[2], debugPoints[3], stairColor[0], 4.0);
            draw_line(debugPoints[3], debugPoints[0], stairColor[0], 2.0);
        }
    }

    if (isTemporary()) {
        Color upC = upColor[0];
        Color leC = leftColor[0];
        Color riC = rightColor[0];
        Color stairC = stairColor[0];
        upC.a = tempAlpha;
        leC.a = tempAlpha;
        riC.a = tempAlpha;
        stairC.a = 0.05;
        upColor.set(0, upC);
        leftColor.set(0, leC);
        rightColor.set(0, riC);
        stairColor.set(0, stairC);

        draw_polygon(upPoints, upColor);
        draw_polygon(leftPoints, leftColor);
        draw_polygon(rightPoints, rightColor);

        if (debugZ >= 0 && debugZ <= (int) size.z) {
            draw_polygon(debugPoints, stairColor);
        }
    } else if (isSelected) {
        drawOutline();
    }
}

void IsometricPlaceholder::updateColors() {
    leftColor = PoolColorArray(Array::make(placeholderType->getColor().darkened(0.5)));
    rightColor = PoolColorArray(Array::make(placeholderType->getColor().darkened(0.25)));
    upColor = PoolColorArray(Array::make(placeholderType->getColor()));
    downColor = PoolColorArray(Array::make(placeholderType->getColor().darkened(0.9)));
    sideSlopeColor = PoolColorArray(Array::make(placeholderType->getColor().darkened(0.10)));
    forwardSlopeColor = PoolColorArray(Array::make(placeholderType->getColor().darkened(0.10)));
    backwardSlopeColor = PoolColorArray(Array::make(placeholderType->getColor().lightened(0.10)));
}

void IsometricPlaceholder::setMapSize(Vector3 size) {
    mapSize = size;
}

void IsometricPlaceholder::_onGridUpdated(int stair) {
    setDebugZ(stair - (int) getPosition3D().z);
    update();
}

void IsometricPlaceholder::_onSelect(bool selected) {
    isSelected = selected;
    update();
}

PlaceholderType *IsometricPlaceholder::getPlaceholderType() const {
    return placeholderType;
}

void IsometricPlaceholder::setPlaceholderType(PlaceholderType *pType) {
    placeholderType = pType;
    updateColors();
}

int IsometricPlaceholder::getSlopeType() {
    return (int) slopeType;
}

void IsometricPlaceholder::setSlopeType(int type) {
    slopeType = (SlopeType) type;
    update();
}
