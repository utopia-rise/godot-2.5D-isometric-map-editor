#include <gen/ResourceLoader.hpp>
#include "IsometricPlaceholder.h"
#include "../helpers/MathHelper.h"
#include "../IsometricServer.h"
#include <gen/Texture.hpp>

using namespace godot;

IsometricPlaceholder::IsometricPlaceholder(): typeColor(0.83, 0.83, 0.83, 1) {

}

void IsometricPlaceholder::_register_methods() {
    register_property("placeholder_type", &IsometricPlaceholder::setPlaceholderType,
            &IsometricPlaceholder::getPlaceholderType,
            (Ref<PlaceholderType>) ResourceLoader::get_singleton()->load("res://addons/IsometricMap/prefab/types/default.tres"));

    register_method("_init", &IsometricPlaceholder::_init);
    register_method("_draw", &IsometricPlaceholder::_draw);
    register_method("get_class", &IsometricPlaceholder::get_class);
}

void IsometricPlaceholder::_init() {
    IsometricPositionable::_init();
    updateColors();
}

void IsometricPlaceholder::_draw() {
    int debugZ { getDebugZ() };
    if (debugZ == static_cast<int>(getSize3D().z)) {
        stairColor = PoolColorArray(Array::make(Color(1, 0.65, 0, 0.2)
                .linear_interpolate(downColor[0], 0.2)));
    } else if (debugZ == 0) {
        stairColor = PoolColorArray(Array::make(Color(0.63, 0.13, 0.94, 0.2)
                .linear_interpolate(downColor[0], 0.2)));
    } else {
        stairColor = PoolColorArray(Array::make(Color(1, 0, 0, 0.2)
                .linear_interpolate(downColor[0], 0.2)));
    }

    switch (static_cast<SlopeType>(getSlopeType())) {
        case SlopeType::NONE:
            break;
        case SlopeType::LEFT:
            upColor = sideSlopeColor;
            break;
        case SlopeType::RIGHT:
            upColor = sideSlopeColor;
            break;
        case SlopeType::FORWARD:
            upColor = forwardSlopeColor;
            break;
        case SlopeType::BACKWARD:
            upColor = backwardSlopeColor;
            break;
    }

    preparePoints();
    drawPoints();
}

String IsometricPlaceholder::get_class() const {
    return "IsometricPlaceholder";
}

void IsometricPlaceholder::drawPoints() {
    const Vector3 &position3D { getPosition3D() };
    const Vector3 &size { getSize3D() };

    int debugZ { getDebugZ() };

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
        stairC.a = 0.5;
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
        auto sizeZInt = static_cast<int>(size.z);
        if (debugZ <= sizeZInt) {
            draw_polygon(debugPoints, stairColor);
            draw_line(debugPoints[0], debugPoints[1], stairColor[0], 2.0);
            draw_line(debugPoints[1], debugPoints[2], stairColor[0], 4.0);
            draw_line(debugPoints[2], debugPoints[3], stairColor[0], 4.0);
            draw_line(debugPoints[3], debugPoints[0], stairColor[0], 2.0);
        }
        real_t zRatio { IsometricServer::getInstance().zRatio };
        int tileWidth { IsometricServer::getInstance().tileWidth };
        int tileHeight { IsometricServer::getInstance().tileHeight };
        float eZ { IsometricServer::getInstance().eZ };

        int correctedZ { clamp(debugZ, 0, sizeZInt) };
        int addedLines { ceil(zRatio * static_cast<float>(correctedZ)) };

        int zDelta { debugZ - correctedZ };
        auto zDeltaFloat = static_cast<real_t>(zDelta);
        real_t offset { (zRatio - 1) * zDeltaFloat };
        auto tileHeightFloat = static_cast<real_t>(tileHeight);
        auto tileWidthFloat = static_cast<real_t>(tileWidth);
        const Vector2 &base { downPoints[0] + Vector2(0, (zDeltaFloat + offset) * tileHeightFloat - eZ * static_cast<real_t>(debugZ)) };

        real_t maxX { mapSize.x - position3D.x - zDeltaFloat - offset };
        real_t maxY { mapSize.y - position3D.y - zDeltaFloat - offset };

        maxX = min(maxX, size.x + static_cast<float>(addedLines) - 1);
        maxY = min(maxY, size.y + static_cast<float>(addedLines) - 1);

        if (maxX > 0 && maxY > 0) {
            for (int i = 0; i < static_cast<int>(maxY + 1); i++) {
                auto iFloat = static_cast<real_t>(i);
                const Vector2 &from { base + Vector2(tileWidthFloat * 0.5f - iFloat, tileHeightFloat * 0.5f * iFloat) };
                const Vector2 &to { base + Vector2(tileWidthFloat * 0.5f * (maxX - iFloat), tileHeightFloat * 0.5f * (maxX + iFloat)) };
                draw_line(from, to, Color(0, 0, 0, 1), 2.0);
            }
            for (int i = 0; i < static_cast<int>(maxX + 1); i++) {
                auto iFloat = static_cast<real_t>(i);
                const Vector2 &from { base + Vector2(tileWidthFloat * 0.5f * iFloat, tileHeightFloat * 0.5f * iFloat) };
                const Vector2 &to { base + Vector2(tileWidthFloat * 0.5f * (iFloat - maxY), tileHeightFloat * 0.5f * (maxY + iFloat)) };
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
    setDebugZ(stair - static_cast<int>(getPosition3D().z));
    update();
}

void IsometricPlaceholder::_onResize() {
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