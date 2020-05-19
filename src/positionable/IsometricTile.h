#ifndef ISOMETRICMAPEDITOR_ISOMETRICTILE_H
#define ISOMETRICMAPEDITOR_ISOMETRICTILE_H

#include <IsometricPositionable.h>
#include "IsometricElement.h"

namespace godot {

    class IsometricTile : public IsometricElement {
        GODOT_SUBCLASS(IsometricTile, IsometricElement)

    public:
        static void _register_methods();

        void _init();
        String get_class() const override;

    };

}


#endif //ISOMETRICMAPEDITOR_ISOMETRICTILE_H
