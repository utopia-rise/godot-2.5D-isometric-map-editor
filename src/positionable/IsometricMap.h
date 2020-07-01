#ifndef ISOMETRICMAPEDITOR_ISOMETRICMAP_H
#define ISOMETRICMAPEDITOR_ISOMETRICMAP_H

#include <IsometricPositionable.h>
#include <Grid3D.h>

namespace godot {
    class IsometricMap : public IsometricPositionable {
        GODOT_SUBCLASS(IsometricMap, IsometricPositionable)

    private:
        bool drawTiles;
        Grid3D grid3D;
        Grid3D editionGrid3D;

        int currentSortingOrder;

        void generateTopologicalRenderGraph();
        void renderIsoNode(IsometricPositionable *isoNode);
        Array getPositionableBehind(IsometricPositionable *isoNode);
        Array getFlattenPositionables(const Vector3 &offset = Vector3());
        IsometricMap *initializeFrom();

    public:

        IsometricMap();
        ~IsometricMap() = default;

        static void _register_methods();

        void _init();
        void _ready();
        void _process(float delta);
        String get_class() const override;

        void addIsoPositionable(IsometricPositionable *isometricPositionable);
        void removeIsoPositionable(IsometricPositionable *isometricPositionable);
        IsometricPositionable *getPositionableAt(Vector3 pos, bool onlyLeftUpperCorner = true);
        bool isOverlapping(IsometricPositionable *positionable);
        bool isOverlappingAABB(AABB aabb);
        bool has(IsometricPositionable *isometricPositionable);
        Array getPositionableChildren() const;

        IsometricMap *flatten();

        void onResize() override;
        void onGridUpdated(int stair) override;
    };
}

#endif //ISOMETRICMAPEDITOR_ISOMETRICMAP_H
