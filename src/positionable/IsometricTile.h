#ifndef ISOMETRICMAPEDITOR_ISOMETRICTILE_H
#define ISOMETRICMAPEDITOR_ISOMETRICTILE_H

#include <IsometricPositionable.h>

namespace godot {

    class IsometricTile : public IsometricPositionable {
        GODOT_SUBCLASS(IsometricTile, IsometricPositionable)

    public:
        static void _register_methods();

        void _init();
        String get_class() const override;
    };

}


#endif //ISOMETRICMAPEDITOR_ISOMETRICTILE_H
