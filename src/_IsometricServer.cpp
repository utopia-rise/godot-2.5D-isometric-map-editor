#include "_IsometricServer.h"
#include "IsometricServer.h"

using namespace godot;

void _IsometricServer::_register_methods() {
    register_property("tile_width", &_IsometricServer::setTileWidth, &_IsometricServer::getTileWidth, 256);
    register_property("tile_height", &_IsometricServer::setTileHeight, &_IsometricServer::getTileHeight, 128);
    register_property("angle", &_IsometricServer::setAngle, &_IsometricServer::getAngle, 30);

    register_method("get_screen_coord_from_3d", &_IsometricServer::getScreenCoordFrom3D);
    register_method("get_3d_coord_from_screen", &_IsometricServer::get3DCoordFromScreen);
}

int _IsometricServer::getTileWidth() {
    return IsometricServer::getTileWidth();
}

void _IsometricServer::setTileWidth(int tile_width) {
    IsometricServer::setTileWidth(tile_width);
}

int _IsometricServer::getTileHeight() {
    return IsometricServer::getTileWidth();
}

void _IsometricServer::setTileHeight(int tile_height) {
    IsometricServer::setTileHeight(tile_height);
}

int _IsometricServer::getAngle() {
    return IsometricServer::getTileHeight();
}

void _IsometricServer::setAngle(int angle) {
    IsometricServer::setAngle(angle);
}

Vector2 _IsometricServer::getScreenCoordFrom3D(Vector3 pos) {
    return IsometricServer::getScreenCoordFrom3D(pos);
}

Vector3 _IsometricServer::get3DCoordFromScreen(Vector2 pos, real_t orthZ) {
    return IsometricServer::get3DCoordFromScreen(pos, orthZ);
}
