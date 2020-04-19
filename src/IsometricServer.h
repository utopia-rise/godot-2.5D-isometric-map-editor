#ifndef ISOMETRICMAPEDITOR_ISOMETRICSERVER_H
#define ISOMETRICMAPEDITOR_ISOMETRICSERVER_H


#include <core/Vector2.hpp>
#include <core/Vector3.hpp>
#include <core/Transform2D.hpp>
#include <core/AABB.hpp>

namespace godot {

#define DEG2RAD(deg) deg / 180 * Math_PI
#define ISO_GROUP "positionables"

    class IsometricServer {
    private:
        static int calculateEz();
    public:
        static int TILE_WIDTH;
        static int TILE_HEIGHT;
        static int ANGLE;
        static int E_Z;
        static int Z_RATIO;

        static int getTileWidth();
        static void setTileWidth(int tile_width);
        static int getTileHeight();
        static void setTileHeight(int tile_height);
        static int getAngle();
        static void setAngle(int angle);

        static Vector2 getScreenCoordFrom3D(Vector3 pos);
        static Vector3 get3DCoordFromScreen(Vector2 pos, real_t orthZ);
        static bool doHexagoneOverlap(Transform2D hex1, Transform2D hex2);
        static bool isBoxInFront(AABB box, AABB other);
    };
}

#endif //ISOMETRICMAPEDITOR_ISOMETRICSERVER_H
