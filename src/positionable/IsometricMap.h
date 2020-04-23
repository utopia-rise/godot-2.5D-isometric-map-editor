#ifndef ISOMETRICMAPEDITOR_ISOMETRICMAP_H
#define ISOMETRICMAPEDITOR_ISOMETRICMAP_H

#include "IsometricPositionable.h"
#include "../containers/Grid3D.h"

namespace godot {
    class IsometricMap : public IsometricPositionable {
        GODOT_SUBCLASS(IsometricMap, IsometricPositionable)

    private:
        bool drawTiles = true;
        Grid3D grid3D = Grid3D();
        Grid3D editionGrid3D = Grid3D();

        int currentSortingOrder = 0;

        void generateTopologicalRenderGraph();
        void renderIsoNode(IsometricPositionable *isoNode);
        Array getPositionableBehind(IsometricPositionable *isoNode);

    public:

        static void _register_methods();

        void _init();
        void _process(float delta);

        void addIsoPositionable(IsometricPositionable *isometricPositionable);
        void removeIsoPositionable(IsometricPositionable *isometricPositionable);
        IsometricPositionable *getPositionableAt(Vector3 pos, bool onlyLeftUpperCorner = true);
        bool isOverlapping(IsometricPositionable *positionable);

        void _onResize() override;
        void _onGridUpdated(int stair) override;
    };
}

#endif //ISOMETRICMAPEDITOR_ISOMETRICMAP_H
