#ifndef ISOMETRICMAPEDITOR_ISOMETRIC_MAP_H
#define ISOMETRICMAPEDITOR_ISOMETRIC_MAP_H

#include "isometric_positionable.h"

namespace godot {
    class IsometricMap : public IsometricPositionable {
        GODOT_CLASS(IsometricMap, IsometricPositionable)

    private:
        bool drawTiles = true;

    public:
        void setDrawTile(bool b);
        void onResize(Vector3 size) override;
    };
}

#endif //ISOMETRICMAPEDITOR_ISOMETRIC_MAP_H
