#include "isometric_map.h"

using namespace godot;

void IsometricMap::setDrawTile(bool b) {
    drawTiles = b;
    update();
}

void IsometricMap::onResize(Vector3 size) {
    //TODO
}