#ifndef ISOMETRICMAPEDITOR_ISOMETRICSERVER_H
#define ISOMETRICMAPEDITOR_ISOMETRICSERVER_H


#include <core/Vector2.hpp>
#include <core/Vector3.hpp>
#include <core/Transform2D.hpp>
#include <core/AABB.hpp>
#include <MathHelper.h>

namespace godot {

#define ISO_GROUP "positionables"

    class IsometricServer {
    private:
        IsometricServer();
        ~IsometricServer() = default;
        int calculateTileHeight() const;
        float calculateEz() const;

    public:
        IsometricServer(const IsometricServer &) = delete;
        IsometricServer &operator=(const IsometricServer &) = delete;

        int tileWidth;
        int tileHeight;
        int angle;
        float eZ;
        float zRatio;

        static IsometricServer &getInstance();

        int getTileWidth() const;
        void setTileWidth(int tW);
        int getTileHeight() const;
        int getAngle() const;
        void setAngle(int agl);

        float getEZ() const;
        double getZRatio() const;

        Vector2 getScreenCoordFrom3D(const Vector3 &pos) const;
        Vector3 get3DCoordFromScreen(const Vector2 &pos, real_t orthZ) const;
        static bool doHexagoneOverlap(const Transform2D &hex1, const Transform2D &hex2);
        static bool isBoxInFront(const AABB &box, const AABB &other);
    };
}

#endif //ISOMETRICMAPEDITOR_ISOMETRICSERVER_H
