#ifndef ISOMETRICMAPEDITOR_ISOMETRIC_UTILS_H
#define ISOMETRICMAPEDITOR_ISOMETRIC_UTILS_H

#include <core/Vector3.hpp>
#include <core/Vector2.hpp>

namespace godot {
    class IsometricUtils {
    public:
        static Vector3 get3DCoordFromScreen(Vector2 pos, int orthZ);
        static Vector2 getScreenCoordFrom3D(Vector3 pos);
    };
}

#endif //ISOMETRICMAPEDITOR_ISOMETRIC_UTILS_H
