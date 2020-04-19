#ifndef ISOMETRICMAPEDITOR_ISOMETRICMAP_H
#define ISOMETRICMAPEDITOR_ISOMETRICMAP_H

#include "IsometricPositionable.h"

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

#endif //ISOMETRICMAPEDITOR_ISOMETRICMAP_H
