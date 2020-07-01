#ifndef ISOMETRICMAPEDITOR_ISOMETRICSERVER_H
#define ISOMETRICMAPEDITOR_ISOMETRICSERVER_H


#include <core/Vector2.hpp>
#include <core/Vector3.hpp>
#include <core/Transform2D.hpp>
#include <core/AABB.hpp>
#include <MathHelper.h>

namespace godot {

#define ISO_GROUP "positionables"

    /**
     * IsometricServer Singleton handles base metrics to handle isometric projections.
     * It uses tile width and an angle of view (vertical) to calculate projections metrics
     */
    class IsometricServer {
    private:
        IsometricServer();
        ~IsometricServer() = default;

        /**
         * @return tileHeight corresponding to tileWidth and angle
         */
        int calculateTileHeight() const;

        /**
         * @return eZ corresponding to tileWidth and angle
         */
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

        /**
         * @return 2D tile width of engine cube meter.
         */
        int getTileWidth() const;

        /**
         * Set 2D tile width of engine cube meter.
         * Calculate also new tile height and eZ.
         * @param tW
         */
        void setTileWidth(int tW);

        /**
         *
         * @return 2D height of lower/upper face of engine cube dimensioned (1, 1, 1).
         */
        int getTileHeight() const;

        /**
         *
         * @return vertical angle of view.
         */
        int getAngle() const;

        /**
         * Set vertical angle of view
         * Calculate also new tile height and eZ.
         * @param agl
         */
        void setAngle(int agl);

        /**
         * @return 2D height of vertical face of engine cube dimensioned (1, 1, 1).
         */
        float getEZ() const;

        /**
         * @return ratio between eZ and tileHeight.
         */
        double getZRatio() const;

        /**
         * @param pos
         * @return 2D coordinates of 3D position `pos`.
         */
        Vector2 getScreenCoordFrom3D(const Vector3 &pos) const;

        /**
         * @param pos
         * @param orthZ
         * @return 3D coordinates using 2D coordinates `pos` and fixed 3D z `orthZ`.
         */
        Vector3 get3DCoordFromScreen(const Vector2 &pos, real_t orthZ) const;

        /**
         * @param hex1
         * @param hex2
         * @return true if hexagone `hex1` overlaps with hexagone `hex2`.
         */
        static bool doHexagoneOverlap(const Transform2D &hex1, const Transform2D &hex2);

        /**
         * @param box
         * @param other
         * @return true if 3D object `box` is in front of 3D object `other`.
         */
        static bool isBoxInFront(const AABB &box, const AABB &other);
    };
}

#endif //ISOMETRICMAPEDITOR_ISOMETRICSERVER_H
