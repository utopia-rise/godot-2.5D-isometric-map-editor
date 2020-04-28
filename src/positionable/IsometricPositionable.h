#ifndef ISOMETRICMAPEDITOR_ISOMETRIC_POSITIONABLE
#define ISOMETRICMAPEDITOR_ISOMETRIC_POSITIONABLE

#include <gen/Node2D.hpp>
#include <core/Godot.hpp>
#include <type_traits>

namespace godot {

#define GODOT_LOG(level, message)\
    switch (level) {\
        case 0:\
            Godot::print(message);\
            break;\
        case 1:\
            Godot::print_warning(message, BOOST_CURRENT_FUNCTION, __FILE__, __LINE__);\
            break;\
        case 2:\
            Godot::print_error(message, BOOST_CURRENT_FUNCTION, __FILE__, __LINE__);\
            break;\
    }\

    class IsometricPositionable : public Node2D {
    GODOT_CLASS(IsometricPositionable, Node2D)

    private:
        AABB aabb;
        int zOrderSize;
        bool rendered = false;
        bool temporary = true;

        int debugZ = 0;

        void updateZOrderSize(int change);

    protected:
        PoolVector2Array leftPoints = PoolVector2Array();
        PoolVector2Array rightPoints = PoolVector2Array();
        PoolVector2Array upPoints = PoolVector2Array();
        PoolVector2Array downPoints = PoolVector2Array();

    public:
        Vector2 isoPosition;
        IsometricPositionable();

        ~IsometricPositionable();

        static void _register_methods();
        void  _init();
        void _enter_tree();
        void _exit_tree();
        virtual String getClass() const;
        Transform2D getHexagoneCoordinates() const;

        void drawOutline();
        AABB getAABB();
        void setAABB(AABB ab);

        Vector3 getPosition3D() const;
        void setPosition3D(Vector3 pos);
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

        virtual void _onResize();
        virtual void _onGridUpdated(int stair);
        virtual void _onSelect(bool selected);
    };
}

#endif //ISOMETRICMAPEDITOR_ISOMETRIC_POSITIONABLE
