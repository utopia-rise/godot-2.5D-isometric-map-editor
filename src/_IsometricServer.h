//GDScript accessors

#ifndef ISOMETRICMAPEDITOR__ISOMETRICSERVER_H
#define ISOMETRICMAPEDITOR__ISOMETRICSERVER_H

#include <core/Godot.hpp>
#include <core/Vector3.hpp>
#include <core/Vector2.hpp>
#include <gen/Node.hpp>

namespace godot {

    /**
     * Exposes IsometricServer singleton to outside of this GDNative.
     */
    class _IsometricServer: public Node {
        GODOT_CLASS(_IsometricServer, Node)
    public:
        static void _register_methods();

        void _init();

        /**
         * @return tileWidth from IsometricServer singleton.
         * @see godot::IsometricServer::getTileWidth
         */
        int getTileWidth();
        void setTileWidth(int tileWidth);

        /**
         * @return tileHeight from IsometricServer singleton.
         * @see godot::IsometricServer::getTileHeight
         */
        int getTileHeight();
        void setTileHeight(int tileHeight);

        /**
         * @return angle of view from IsometricServer singleton.
         * @see godot::IsometricServer::getAngle
         */
        int getAngle();
        void setAngle(int angle);

        /**
         * @return eZ from IsometricServer singleton.
         * @see godot::IsometricServer::getEZ
         */
        double getEZ();

        /**
         * @return zRatio from IsometricServer singleton.
         * @see godot::IsometricServer::getZRatio
         */
        double getZRatio();

        /**
         * @param pos
         * @return 2D screen coordinates by calling IsometricServer singleton.
         * @see godot::IsometricServer::getScreenCoordFrom3D
         */
        Vector2 getScreenCoordFrom3D(Vector3 pos);

        /**
         * @param pos
         * @param orthZ
         * @return 3D coordinates by calling IsometricServer singleton.
         * @see godot::IsometricServer::get3DCoordFromScreen
         */
        Vector3 get3DCoordFromScreen(Vector2 pos, real_t orthZ);
    };
}

#endif //ISOMETRICMAPEDITOR__ISOMETRICSERVER_H
