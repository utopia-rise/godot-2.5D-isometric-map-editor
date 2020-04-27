#ifndef ISOMETRICMAPEDITOR_ISOMETRICSERVER_H
#define ISOMETRICMAPEDITOR_ISOMETRICSERVER_H


#include <core/Vector2.hpp>
#include <core/Vector3.hpp>
#include <core/Transform2D.hpp>
#include <core/AABB.hpp>
#include "helpers/MathHelper.h"

namespace godot {

#define ISO_GROUP "positionables"

    class IsometricServer {
    private:
        IsometricServer();
        ~IsometricServer();
        int calculateEz() const;

    public:
        IsometricServer(const IsometricServer &) = delete;
        IsometricServer &operator=(const IsometricServer &) = delete;

        int tileWidth = 256;
        int tileHeight = 128;
        int angle = 30;
        double eZ = ((double) tileHeight / sin(DEG2RAD((double) angle)) / sqrt(2)) * cos(DEG2RAD((double) angle));
        double zRatio = (double) eZ / (double) tileHeight;

        static IsometricServer &getInstance();

        int getTileWidth() const;
        void setTileWidth(int tW);
        int getTileHeight() const;
        void setTileHeight(int tH);
        int getAngle() const;
        void setAngle(int agl);

        double getEZ() const;
        double getZRatio() const;

        Vector2 getScreenCoordFrom3D(Vector3 pos) const;
        Vector3 get3DCoordFromScreen(Vector2 pos, real_t orthZ) const;
        static bool doHexagoneOverlap(Transform2D hex1, Transform2D hex2);
        static bool isBoxInFront(AABB box, AABB other);
    };
}

#endif //ISOMETRICMAPEDITOR_ISOMETRICSERVER_H
