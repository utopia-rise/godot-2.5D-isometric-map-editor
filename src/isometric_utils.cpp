#include "isometric_utils.h"

using namespace godot;

const int IsometricUtils::TILE_WIDTH = 256;
const int IsometricUtils::TILE_DEPTH = 128;
const int IsometricUtils::TILE_HEIGHT = 128;
const int IsometricUtils::E_Z = static_cast<int>((TILE_HEIGHT / sin(deg2rad(30)) / sqrt(2)) * cos(deg2rad(30)));

Vector3 IsometricUtils::get3DCoordFromScreen(Vector2 pos, real_t orthZ) {
    auto isoX = pos.x;
    auto isoY = pos.y;
    real_t orthX = isoX / TILE_WIDTH + (isoY + orthZ * E_Z) / TILE_HEIGHT;
    real_t orthY = (isoY + orthZ * E_Z) / TILE_HEIGHT - isoX / TILE_WIDTH;
    return {
        ::roundf(orthX),
        ::roundf(orthY),
        ::roundf(orthZ)
    };
}

Vector2 IsometricUtils::getScreenCoordFrom3D(Vector3 pos) {
    return {
        (pos.x - pos.y) * TILE_WIDTH * 0.5f,
        (pos.x + pos.y) * TILE_HEIGHT * 0.5f
    };
}
