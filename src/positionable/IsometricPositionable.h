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
        PoolVector2Array leftPoints;
        PoolVector2Array rightPoints;
        PoolVector2Array upPoints;

        PoolVector2Array downPoints;

        void updateZOrderSize(int change);

    protected:
        template<typename T>
        T *_new(T *original) {
            static_assert(std::is_base_of<IsometricPositionable, T>::value, "T must be an IsometricPositionable based class.");
            T *copy = T::_new();
            copy->setAABB(original->aabb);
            return copy;
        }

    public:

        Vector2 isoPosition;
        IsometricPositionable();

        ~IsometricPositionable();

        static void _register_methods();
        void  _init();
        void _enter_tree();
        void _exit_tree();
        Transform2D getHexagoneCoordinates() const;

        void drawOutline();
        AABB getAABB();

        void setAABB(AABB ab);
        Vector3 getPosition3D();
        void setPosition3D(Vector3 pos);
        Vector3 getSize3D();
        void setSize3D(Vector3 s);
        int getZOrderSize() const;
        void setZOrderSize(int size);
        bool isRendered() const;
        void setRendered(bool isRendered);
        bool isTemporary() const;
        void setTemporary(bool temp);
        int getDebugZ() const;
        void setDebugZ(int dZ);

        virtual IsometricPositionable *copy();

        virtual void _onResize();
        virtual void _onGridUpdated(int stair);
        virtual void _onSelect(bool isSelected);
    };
}

#endif //ISOMETRICMAPEDITOR_ISOMETRIC_POSITIONABLE
