#ifndef ISOMETRICMAPEDITOR_DEFAULTBODY_H
#define ISOMETRICMAPEDITOR_DEFAULTBODY_H


#include <positionable/IsometricElement.h>
#include <gen/CollisionShape.hpp>
#include <ConvexPolygonShape.hpp>

namespace godot {

    template<class T, class U>
    class DefaultBody {

    protected:
        IsometricElement<T> *parent;
        U *shape;
        CollisionShape *collisionShape;

        void initializeShapes();

        virtual void calculateCollisionShape();

        virtual void updateCollisionShapes();

    public:
        DefaultBody();

        ~DefaultBody() = default;

        /**
         * Sets the parent node of this DefaultBody. Should be an IsometricElement.
         * @param isometricElement
         */
        void setParent(IsometricElement<T> *isometricElement);
    };

    template<class T, class U>
    DefaultBody<T, U>::DefaultBody(): parent(nullptr), shape(nullptr), collisionShape(nullptr) {

    }

    template<class T, class U>
    void DefaultBody<T, U>::setParent(IsometricElement<T> *isometricElement) {
        parent = isometricElement;
    }

    template<class T, class U>
    void DefaultBody<T, U>::calculateCollisionShape() {

    }

    template<class T, class U>
    void DefaultBody<T, U>::updateCollisionShapes() {

    }

    template<class T, class U>
    void DefaultBody<T, U>::initializeShapes() {
        collisionShape = CollisionShape::_new();
        shape = U::_new();
    }
}


#endif //ISOMETRICMAPEDITOR_DEFAULTBODY_H
