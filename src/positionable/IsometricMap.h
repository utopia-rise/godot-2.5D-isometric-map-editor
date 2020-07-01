#ifndef ISOMETRICMAPEDITOR_ISOMETRICMAP_H
#define ISOMETRICMAPEDITOR_ISOMETRICMAP_H

#include <IsometricPositionable.h>
#include <Grid3D.h>

namespace godot {

    /**
     * IsometricPositionable designed to contains other IsometricPositionable.
     * This means you can store in it tiles, placeholder, but also other maps.
     * Calculate the render ordering using a topological graph.
     * @inherit godot::IsometricPositionable
     */
    class IsometricMap : public IsometricPositionable {
        GODOT_SUBCLASS(IsometricMap, IsometricPositionable)

    private:
        bool drawTiles;
        Grid3D grid3D;
        Grid3D editionGrid3D;

        int currentSortingOrder;

        /**
         * Entry method to generate topological graph for rendering order of elements.
         */
        void generateTopologicalRenderGraph();

        /**
         * Calculate z_index of all elements contained in IsometricMap.
         * @param isoNode
         */
        void renderIsoNode(IsometricPositionable *isoNode);

        /**
         * Find IsometricPositionable behing `isoNode` using godot::IsometricServer::doHexagoneOverlap and
         * IsometricServer::isBoxInFront
         * @param isoNode
         * @return Array of IsometricPositionables behing `isoNode`
         * @see godot::IsometricServer::doHexagoneOverlap
         * @see godot::IsometricServer::isBoxInFront
         */
        Array getPositionableBehind(IsometricPositionable *isoNode);

        /**
         * @param offset
         * @return Array containing a flatten copy of children IsometricPopsitionables. It means maps contained in
         * this map are flatten.
         */
        Array getFlattenPositionables(const Vector3 &offset = Vector3());

        /**
         * @return A new map with the same dimension as this one.
         */
        IsometricMap *initializeFrom();

    public:

        IsometricMap();
        ~IsometricMap() = default;

        static void _register_methods();

        void _init();
        void _ready();
        void _process(float delta);
        String get_class() const override;

        /**
         * Add isometricPositionable in this map. Use Gris3D and position of IsometricPositionable we insert.
         * @param isometricPositionable
         */
        void addIsoPositionable(IsometricPositionable *isometricPositionable);

        /**
         * Remove an existing IsometricPositionable from this map.
         * @param isometricPositionable
         */
        void removeIsoPositionable(IsometricPositionable *isometricPositionable);

        /**
         * @param pos
         * @param onlyLeftUpperCorner
         * @return The positionable at the position `pos`. If `onlyLeftUpperCorner` is true it does not take care of
         * the size of positionables, only its position.
         * Returns nullptr if no IsometricPositionable was found.
         */
        IsometricPositionable *getPositionableAt(Vector3 pos, bool onlyLeftUpperCorner = true);

        /**
         * @param positionable
         * @return true if `positionable` overlaps with existing IsometricPositionable in map.
         */
        bool isOverlapping(IsometricPositionable *positionable);

        /**
         * @param aabb
         * @return true if `aabb` overlaps with existing IsometricPositionable in map.
         */
        bool isOverlappingAABB(AABB aabb);

        /**
         * @param isometricPositionable
         * @return true if map contains `isometricPositionable`
         */
        bool has(IsometricPositionable *isometricPositionable);

        /**
         * Returns positionable contained in this map.
         *
         * This should not be used often.
         *
         * @return a copy array containing positionable children.
         */
        Array getPositionableChildren() const;

        /**
         * Here to export map for game build.
         * @return a copy map with flatten children using godot::IsometricMap::getFlattenPositionables
         * @see godot::IsometricMap::getFlattenPositionables
         */
        IsometricMap *flatten();

        void _onResize() override;
        void _onGridUpdated(int stair) override;
    };
}

#endif //ISOMETRICMAPEDITOR_ISOMETRICMAP_H
