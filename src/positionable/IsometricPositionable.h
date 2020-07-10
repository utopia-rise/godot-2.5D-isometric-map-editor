#ifndef ISOMETRICMAPEDITOR_ISOMETRIC_POSITIONABLE
#define ISOMETRICMAPEDITOR_ISOMETRIC_POSITIONABLE

#include <gen/Node2D.hpp>
#include <core/Godot.hpp>
#include <type_traits>
#include <OutlineDrawer.h>

namespace godot {

    enum class SlopeType {NONE = 0, LEFT = 1, RIGHT = 2, FORWARD = 3, BACKWARD = 4};

    class IsometricPositionable : public Node2D {
    GODOT_CLASS(IsometricPositionable, Node2D)

    private:
        AABB aabb;
        int zOrderSize;
        bool rendered;
        bool temporary;

        int debugZ;

        void updateZOrderSize(int change);

    protected:
        OutlineDrawer *outlineDrawer;

        PoolVector2Array leftPoints;
        PoolVector2Array rightPoints;
        PoolVector2Array upPoints;
        PoolVector2Array downPoints;

        PoolVector2Array debugPoints;

        void preparePoints();
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
        Transform2D getHexagoneCoordinates() const;
        void setOutlineDrawer(Color color, real_t lineSize);
        Vector3 getPositionOffset() const;

        AABB getAABB();
        virtual void setAABB(AABB ab);
        Vector3 getPosition3D() const;
        virtual void setPosition3D(Vector3 pos);
        Vector3 getSize3D() const;
        void setSize3D(Vector3 s);
        int getZOrderSize() const;
        void setZOrderSize(int size);
        bool isRendered() const;
        void setRendered(bool isRendered);
        bool isTemporary() const;
        void setTemporary(bool temp);
        int getDebugZ() const;
        void setDebugZ(int dZ);

        virtual void onResize();
        virtual void onGridUpdated(int stair);
        virtual void onSelect(bool selected);
        virtual bool getHasMoved() const;
        virtual void setHasMoved(bool hm);
    };
}

#endif //ISOMETRICMAPEDITOR_ISOMETRIC_POSITIONABLE
