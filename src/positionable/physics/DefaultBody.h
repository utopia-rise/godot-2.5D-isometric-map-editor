#ifndef ISOMETRICMAPEDITOR_DEFAULTBODY_H
#define ISOMETRICMAPEDITOR_DEFAULTBODY_H


#include <positionable/IsometricElement.h>
#include <gen/CollisionShape.hpp>
#include <ConvexPolygonShape.hpp>

namespace godot {

    template<class T>
    class DefaultBody {

    protected:
        IsometricElement<T> *parent;
        ConvexPolygonShape *convexPolygonShape;
        CollisionShape *collisionShape;

        void initializeShapes();

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
    DefaultBody<T>::DefaultBody(): parent(nullptr), convexPolygonShape(nullptr), collisionShape(nullptr) {

    }

    template<class T>
    void DefaultBody<T>::setParent(IsometricElement<T> *isometricElement) {
        parent = isometricElement;
    }

    template<class T>
    void DefaultBody<T>::updateCollisionShapes() {

    }

    template<class T>
    void DefaultBody<T>::initializeShapes() {
        collisionShape = CollisionShape::_new();
        convexPolygonShape = ConvexPolygonShape::_new();
    }

    template<class T>
    void DefaultBody<T>::calculateCollisionShape() {
        auto slopeType = static_cast<SlopeType>(parent->getSlopeType());
        const Vector3 &size = parent->getSize3D();

        const Vector3 &convertedSize{size.x, size.z, size.y};
        Vector3 originPoint;
        PoolVector3Array poolVector3Array;
        poolVector3Array.push_back(originPoint);
        poolVector3Array.push_back({originPoint.x, 0, convertedSize.z});
        poolVector3Array.push_back({convertedSize.x, 0, originPoint.z});
        poolVector3Array.push_back({convertedSize.x,0, convertedSize.z});

        switch (slopeType) {
            case SlopeType::NONE:
                poolVector3Array.push_back({originPoint.x, convertedSize.y, originPoint.z});
                poolVector3Array.push_back({originPoint.x, convertedSize.y, convertedSize.z});
                poolVector3Array.push_back({convertedSize.x, convertedSize.y, originPoint.z});
                poolVector3Array.push_back(convertedSize);
                break;
            case SlopeType::LEFT:
                poolVector3Array.push_back({originPoint.x, convertedSize.y, originPoint.z});
                poolVector3Array.push_back({originPoint.x, convertedSize.y, convertedSize.z});
                break;
            case SlopeType::RIGHT:
                poolVector3Array.push_back({convertedSize.x, convertedSize.y, originPoint.z});
                poolVector3Array.push_back(convertedSize);
                break;
            case SlopeType::FORWARD:
                poolVector3Array.push_back({originPoint.x, convertedSize.y, originPoint.z});
                poolVector3Array.push_back({convertedSize.x, convertedSize.y, originPoint.z});
                break;
            case SlopeType::BACKWARD:
                poolVector3Array.push_back({originPoint.x, convertedSize.y, convertedSize.z});
                poolVector3Array.push_back(convertedSize);
                break;
        }

        convexPolygonShape->set_points(poolVector3Array);
        collisionShape->set_shape(convexPolygonShape);
    }
}


#endif //ISOMETRICMAPEDITOR_DEFAULTBODY_H
