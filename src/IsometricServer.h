#ifndef ISOMETRICMAPEDITOR_ISOMETRICSERVER_H
#define ISOMETRICMAPEDITOR_ISOMETRICSERVER_H


#include <core/Vector2.hpp>
#include <core/Vector3.hpp>

namespace godot {

#define deg2rad(deg) deg / 180 * Math_PI

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
    };
}

#endif //ISOMETRICMAPEDITOR_ISOMETRICSERVER_H
