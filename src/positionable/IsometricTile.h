#ifndef ISOMETRICMAPEDITOR_ISOMETRICTILE_H
#define ISOMETRICMAPEDITOR_ISOMETRICTILE_H

#include "IsometricPositionable.h"

namespace godot {

    class IsometricTile : public IsometricPositionable {
        GODOT_SUBCLASS(IsometricTile, IsometricPositionable)

    public:
        void _init();
        static void _register_methods();
    };

}


#endif //ISOMETRICMAPEDITOR_ISOMETRICTILE_H
