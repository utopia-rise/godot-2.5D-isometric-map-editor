#ifndef ISOMETRICMAPEDITOR_DEFAULTBODY_H
#define ISOMETRICMAPEDITOR_DEFAULTBODY_H


#include <positionable/IsometricElement.h>
#include <gen/CollisionShape.hpp>
#include <ConvexPolygonShape.hpp>

namespace godot {

    template <class T>
    class DefaultBody {

    protected:
        IsometricElement<T> *parent;
        ConvexPolygonShape *convexPolygonShape;
        int shapeOwner;

        void calculateCollisionShape();
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

    template<class T>
    DefaultBody<T>::DefaultBody(): parent(nullptr), convexPolygonShape(nullptr), shapeOwner(0) {

    }

    template<class T>
    void DefaultBody<T>::setParent(IsometricElement<T> *isometricElement) {
        parent = isometricElement;
    }

    template<class T>
    void DefaultBody<T>::updateCollisionShapes() {

    }

    template<class T>
    void DefaultBody<T>::calculateCollisionShape() {
        auto slopeType = static_cast<SlopeType>(parent->getSlopeType());
        const Vector3 &size = parent->getSize3D();

        PoolVector3Array poolVector3Array;
        Vector3 originPoint;
        poolVector3Array.push_back(originPoint);
        poolVector3Array.push_back(originPoint + Vector3(0, 0, size.y));
        poolVector3Array.push_back(originPoint + Vector3(size.x, 0, 0));
        poolVector3Array.push_back(originPoint + Vector3(size.x, 0, size.y));

        switch (slopeType) {
            case SlopeType::NONE:
                poolVector3Array.push_back(originPoint + Vector3(0, size.z, 0));
                poolVector3Array.push_back(originPoint + Vector3(0, size.z, size.y));
                poolVector3Array.push_back(originPoint + Vector3(size.x, size.z, 0));
                poolVector3Array.push_back(originPoint + Vector3(size.x, size.z, size.y));
                break;
            case SlopeType::LEFT:
                poolVector3Array.push_back(originPoint + Vector3(0, size.z, 0));
                poolVector3Array.push_back(originPoint + Vector3(0, size.z, size.y));
                break;
            case SlopeType::RIGHT:
                poolVector3Array.push_back(originPoint + Vector3(size.x, size.z, 0));
                poolVector3Array.push_back(originPoint + Vector3(size.x, size.z, size.y));
                break;
            case SlopeType::FORWARD:
                poolVector3Array.push_back(originPoint + Vector3(0, size.z, 0));
                poolVector3Array.push_back(originPoint + Vector3(size.x, size.z, 0));
                break;
            case SlopeType::BACKWARD:
                poolVector3Array.push_back(originPoint + Vector3(0, size.z, size.y));
                poolVector3Array.push_back(originPoint + Vector3(size.x, size.z, size.y));
                break;
        }

        convexPolygonShape->set_points(poolVector3Array);
    }

}


#endif //ISOMETRICMAPEDITOR_DEFAULTBODY_H
