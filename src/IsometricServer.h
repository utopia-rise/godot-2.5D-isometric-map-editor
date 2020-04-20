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
        IsometricServer();
        ~IsometricServer();
        int calculateEz();

    public:
        IsometricServer(const IsometricServer &) = delete;
        IsometricServer &operator=(const IsometricServer &) = delete;

        int tileWidth = 256;
        int tileHeight = 128;
        int angle = 30;
        int eZ = (int) ((tileHeight / sin(DEG2RAD((float) angle)) / sqrt(2)) * cos(DEG2RAD((float) angle)));;
        float zRatio = (float) eZ / tileHeight;

        static IsometricServer &getInstance();

        int getTileWidth();
        void setTileWidth(int tW);
        int getTileHeight();
        void setTileHeight(int tH);
        int getAngle();
        void setAngle(int agl);

        int getEZ();
        int getZRatio();

        Vector2 getScreenCoordFrom3D(Vector3 pos);
        Vector3 get3DCoordFromScreen(Vector2 pos, real_t orthZ);
        bool doHexagoneOverlap(Transform2D hex1, Transform2D hex2);
        bool isBoxInFront(AABB box, AABB other);
    };
}

#endif //ISOMETRICMAPEDITOR_ISOMETRICSERVER_H
