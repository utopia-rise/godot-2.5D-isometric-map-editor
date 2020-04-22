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

void _IsometricServer::_init() {}

int _IsometricServer::getTileWidth() {
    return IsometricServer::getInstance().getTileWidth();
}

void _IsometricServer::setTileWidth(int tileWidth) {
    IsometricServer::getInstance().setTileWidth(tileWidth);
}

int _IsometricServer::getTileHeight() {
    return IsometricServer::getInstance().getTileHeight();
}

void _IsometricServer::setTileHeight(int tileHeight) {
    IsometricServer::getInstance().setTileHeight(tileHeight);
}

int _IsometricServer::getAngle() {
    return IsometricServer::getInstance().getAngle();
}

void _IsometricServer::setAngle(int angle) {
    IsometricServer::getInstance().setAngle(angle);
}

Vector2 _IsometricServer::getScreenCoordFrom3D(Vector3 pos) {
    return IsometricServer::getInstance().getScreenCoordFrom3D(pos);
}

Vector3 _IsometricServer::get3DCoordFromScreen(Vector2 pos, real_t orthZ) {
    return IsometricServer::getInstance().get3DCoordFromScreen(pos, orthZ);
}
