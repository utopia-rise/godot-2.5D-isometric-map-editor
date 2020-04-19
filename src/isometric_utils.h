#ifndef ISOMETRICMAPEDITOR_ISOMETRIC_UTILS_H
#define ISOMETRICMAPEDITOR_ISOMETRIC_UTILS_H

#include <core/Vector3.hpp>
#include <core/Vector2.hpp>

namespace godot {

#define deg2rad(deg) deg / 180 * Math_PI

    class IsometricUtils {
    public:
        static const int TILE_WIDTH; //TODO read with JSON
        static const int TILE_DEPTH; //TODO read with JSON
        static const int TILE_HEIGHT; //TODO read with JSON
        static const int E_Z;

        static Vector3 get3DCoordFromScreen(Vector2 pos, real_t orthZ);
        static Vector2 getScreenCoordFrom3D(Vector3 pos);
    };
}

#endif //ISOMETRICMAPEDITOR_ISOMETRIC_UTILS_H
