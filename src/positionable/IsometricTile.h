#ifndef ISOMETRICMAPEDITOR_ISOMETRICTILE_H
#define ISOMETRICMAPEDITOR_ISOMETRICTILE_H

#include <IsometricPositionable.h>
#include "IsometricElement.h"

namespace godot {

    /**
     * Represents a tile, i.e. a drawing unit created with assets (like sprite, particles emitter, whatever node you
     * want).
     * @inherit godot::IsometricElement
     */
    class IsometricTile : public IsometricElement {
        GODOT_SUBCLASS(IsometricTile, IsometricElement)

    public:
        static void _register_methods();

        void _init();
        String get_class() const override;

    };

}


#endif //ISOMETRICMAPEDITOR_ISOMETRICTILE_H
