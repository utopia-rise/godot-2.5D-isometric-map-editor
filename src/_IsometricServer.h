//GDScript accessors

#ifndef ISOMETRICMAPEDITOR__ISOMETRICSERVER_H
#define ISOMETRICMAPEDITOR__ISOMETRICSERVER_H

#include <core/Godot.hpp>
#include <core/Vector3.hpp>
#include <core/Vector2.hpp>
#include <gen/Node.hpp>

namespace godot {

    class _IsometricServer: public Node {
        GODOT_CLASS(_IsometricServer, Node)
    public:
        static void _register_methods();

        int getTileWidth();
        void setTileWidth(int tile_width);
        int getTileHeight();
        void setTileHeight(int tile_height);
        int getAngle();
        void setAngle(int angle);

        Vector2 getScreenCoordFrom3D(Vector3 pos);
        Vector3 get3DCoordFromScreen(Vector2 pos, real_t orthZ);
    };
}

#endif //ISOMETRICMAPEDITOR__ISOMETRICSERVER_H
