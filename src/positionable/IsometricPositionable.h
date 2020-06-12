#ifndef ISOMETRICMAPEDITOR_ISOMETRIC_POSITIONABLE
#define ISOMETRICMAPEDITOR_ISOMETRIC_POSITIONABLE

#include <gen/Node2D.hpp>
#include <core/Godot.hpp>
#include <type_traits>
#include <OutlineDrawer.h>

namespace godot {

    enum class SlopeType {NONE = 0, LEFT = 1, RIGHT = 2, FORWARD = 3, BACKWARD = 4};

    /**
     * Represents a parallelepiped that has 3D position and size.
     * This 3D object is then projected in the 2D part of engine.
     * IsometricPositionable is the base class of all 3D objects of this addon.
     */
    class IsometricPositionable : public Node2D {
    GODOT_CLASS(IsometricPositionable, Node2D)

    private:
        AABB aabb;
        int zOrderSize;
        bool rendered;
        bool temporary;

        int debugZ;

        /**
         * Update parent's placeholder zOrderSize if parent is IsometricPositionable.
         * @param change
         */
        void updateZOrderSize(int change);

    protected:
        OutlineDrawer *outlineDrawer;

        PoolVector2Array leftPoints;
        PoolVector2Array rightPoints;
        PoolVector2Array upPoints;
        PoolVector2Array downPoints;

        PoolVector2Array debugPoints;

        /**
         * Prepare points representing edges of IsometricPositionable.
         */
        void preparePoints();

        /**
         * Set slopeOffset value for drawing purpose.
         * @param slopeOffset
         * @param tileWidthFloat
         * @param tileHeightFloat
         * @param width
         * @param depth
         * @param ratio
         * @return SlopeType of IsometricPositionable.
         */
        virtual SlopeType
        calculateSlopeOffset(Vector2 *slopeOffset, real_t tileWidthFloat, real_t tileHeightFloat, real_t width,
                             real_t depth,
                             real_t ratio) const;
    public:
        Vector2 isoPosition;
        IsometricPositionable();
        ~IsometricPositionable() = default;

        static void _register_methods();

        void  _init();
        void _enter_tree();
        void _exit_tree();
        virtual String get_class() const;

        /**
         * @return Transform2D in which each coordinates represents hexagone dimensions
         */
        Transform2D getHexagoneCoordinates() const;

        /**
         * Set outline drawer with provided color and line thickness.
         * Here for edition purpose.
         * @param color
         * @param lineSize
         */
        void setOutlineDrawer(Color color, real_t lineSize);

        /**
         * @return AABB representing the 3D dimensions of IsometricPositionable.
         */
        AABB getAABB();

        /**
         * Sets 3D dimensions of IsometricPositionable
         * @param ab
         */
        void setAABB(AABB ab);

        /**
         * @return Vector3 representing 3D position of IsometricPositionable.
         */
        Vector3 getPosition3D() const;

        /**
         * Sets 3D position of IsometricPositionable.
         * @param pos
         */
        void setPosition3D(Vector3 pos);

        /**
         * @return 3D size of IsometricPositionable.
         */
        Vector3 getSize3D() const;

        /**
         * Sets 3D size of IsometricPositionable
         * @param s
         */
        void setSize3D(Vector3 s);

        /**
         * @return zOrderSize of this IsometricPositionable.
         */
        int getZOrderSize() const;

        /**
         * Sets zOrderSize of this IsometricPositionable and its parents by calling
         * godot::IsometricPositionable::updateZOrderSize
         * @param size
         * @see godot::IsometricPositionable::updateZOrderSize
         */
        void setZOrderSize(int size);

        /**
         * @return true if this isometricPositionable is rendered.
         */
        bool isRendered() const;

        /**
         * Use when we want to notify IsometricPositionable is rendered or not.
         * @param isRendered
         */
        void setRendered(bool isRendered);

        /**
         * @return true if this IsometricPositionable is temporary
         * Here for edition purpose.
         */
        bool isTemporary() const;

        /**
         * Set temporary to ``temp` value.
         * @param temp
         */
        void setTemporary(bool temp);

        /**
         * @return debugZ of this IsometricPositionable
         * Here for edition purpose.
         */
        int getDebugZ() const;

        /**
         * Sets the debugZ value to `dZ`.
         * Here for edition purpose.
         * @param dZ
         */
        void setDebugZ(int dZ);

        /**
         * Should be triggered when resizing an IsometricPositionable.
         */
        virtual void _onResize();

        /**
         * Should be called when updating EditionGrid.
         * Here for edition purpose.
         * @param stair
         */
        virtual void _onGridUpdated(int stair);

        /**
         * Should be called when selecting an IsometricPositionable.
         * Here for edition purpose.
         * @param selected
         */
        virtual void _onSelect(bool selected);
    };
}

#endif //ISOMETRICMAPEDITOR_ISOMETRIC_POSITIONABLE
