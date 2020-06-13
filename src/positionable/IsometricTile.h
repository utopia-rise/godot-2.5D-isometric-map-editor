#ifndef ISOMETRICMAPEDITOR_ISOMETRICTILE_H
#define ISOMETRICMAPEDITOR_ISOMETRICTILE_H

#include <StaticIsometricElement.h>

namespace godot {

    class IsometricTile : public StaticIsometricElement {
        GODOT_SUBCLASS(IsometricTile, StaticIsometricElement)

    public:
        static void _register_methods();

        void _init();
        String get_class() const override;

    };

}


#endif //ISOMETRICMAPEDITOR_ISOMETRICTILE_H
