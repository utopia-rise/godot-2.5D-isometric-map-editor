#ifndef ISOMETRICMAPEDITOR_ISOMETRICELEMENT_H
#define ISOMETRICMAPEDITOR_ISOMETRICELEMENT_H

#include <Godot.hpp>
#include <IsometricPositionable.h>
#include <gen/PhysicsServer.hpp>
#include <gen/World.hpp>
#include <gen/PhysicsDirectSpaceState.hpp>
#include <gen/Shape.hpp>
#include <gen/ConvexPolygonShape.hpp>

namespace godot {

    template <class T>
    class IsometricElement : public IsometricPositionable {

    private:
        PhysicsBody *registeredBody;

    protected:
        bool hasMoved;
        bool hasDefaultBody;
        T *defaultBody;

        /**
         * Sets or remove defaultBody in function of hasDefaultBody
         */
        void updateDefaultBody();

    public:
        IsometricElement();
        ~IsometricElement() = default;

        void _enter_tree();
        String get_class() const override;

        /**
         * @return true if should have default body.
         */
        virtual bool getHasDefaultBody() const;

        /**
         * Sets if StaticIsometricElement should have default body.
         * @param b
         */
        virtual void setHasDefaultBody(bool b);

        virtual PhysicsBody *getRegisteredBody() const;
        virtual void setRegisteredBody(PhysicsBody *physicsBody);

        virtual void updatePositionFromBody(PhysicsBody *physicsBody);

        virtual int getSlopeType() const;

        void setAABB(AABB ab) override;
        void setPosition3D(Vector3 pos) override;
        void onResize() override;
        bool getHasMoved() const override;
        void setHasMoved(bool hm) override;
        bool isColliding(PhysicsShapeQueryParameters *physicsQuery, bool isEdition) const override;
        bool isCollidingAABB(bool isEdition) const override;
    };

    template<class T>
    IsometricElement<T>::IsometricElement(): hasMoved(false), hasDefaultBody(true), defaultBody(nullptr) {

    }

    template<class T>
    void IsometricElement<T>::_enter_tree() {
        IsometricPositionable::_enter_tree();
        const Array &children = get_children();
        if (hasDefaultBody) {
            for (int i = 0; i < children.size(); i++) {
                auto *body = cast_to<T>(children[i]);
                if (body) {
                    defaultBody = body;
                    defaultBody->setParent(this);
                    defaultBody->set_owner(this);
                    break;
                }
            }
        }
        updateDefaultBody();
    }

    template<class T>
    bool IsometricElement<T>::getHasDefaultBody() const {
        return hasDefaultBody;
    }

    template<class T>
    void IsometricElement<T>::setHasDefaultBody(bool b) {
        hasDefaultBody = b;
        if (is_inside_tree()) {
            updateDefaultBody();
        }
    }

    template<class T>
    void IsometricElement<T>::updatePositionFromBody(PhysicsBody *physicsBody) {
        const Vector3 &origin = physicsBody->get_global_transform().origin;
        IsometricPositionable::setPosition3D({origin.x, origin.z, origin.y});
    }

    template<class T>
    int IsometricElement<T>::getSlopeType() const {
        return static_cast<int>(SlopeType::NONE);
    }

    template<class T>
    void IsometricElement<T>::setAABB(AABB ab) {
        IsometricPositionable::setAABB(ab);
        hasMoved = true;
    }

    template<class T>
    void IsometricElement<T>::setPosition3D(Vector3 pos) {
        IsometricPositionable::setPosition3D(pos);
        hasMoved = true;
    }

    template<class T>
    void IsometricElement<T>::updateDefaultBody() {
        if (hasDefaultBody) {
            if (!defaultBody) {
                defaultBody = T::_new();
                defaultBody->setParent(this);
                add_child(defaultBody);
                defaultBody->set_owner(this);
                hasMoved = true;
            }
        } else {
            if (defaultBody) {
                remove_child(defaultBody);
                defaultBody->queue_free();
                defaultBody = nullptr;
            }
        }
    }

    template<class T>
    void IsometricElement<T>::onResize() {
        IsometricPositionable::onResize();
        hasMoved = true;
    }

    template<class T>
    bool IsometricElement<T>::getHasMoved() const {
        return hasMoved;
    }

    template<class T>
    void IsometricElement<T>::setHasMoved(bool hm) {
        hasMoved = hm;
    }

    template<class T>
    String IsometricElement<T>::get_class() const {
        return "IsometricElement";
    }

    template<class T>
    PhysicsBody *IsometricElement<T>::getRegisteredBody() const {
        return registeredBody;
    }

    template<class T>
    void IsometricElement<T>::setRegisteredBody(PhysicsBody *physicsBody) {
        registeredBody = physicsBody;
    }

    template<class T>
    bool IsometricElement<T>::isColliding(PhysicsShapeQueryParameters *physicsQuery, bool isEdition) const {
        if (registeredBody) {
            Ref<World> world = registeredBody->get_world();
            if (world.is_valid()) {
                PhysicsDirectSpaceState *physicsDirectSpaceState = world.ptr()->get_direct_space_state();
                if (physicsQuery && !physicsDirectSpaceState->intersect_shape(physicsQuery, 1).empty()) {
                    return true;
                } else {
                    const Array &shapeOwners { registeredBody->get_shape_owners() };
                    for (int i = 0; i < shapeOwners.size(); i++) {
                        uint32_t owner = shapeOwners[i];
                        for (int j = 0; j < registeredBody->shape_owner_get_shape_count(owner); j++) {
                            PhysicsShapeQueryParameters *parameters = PhysicsShapeQueryParameters::_new();
                            const Transform &transform { registeredBody->get_transform() };
                            parameters->set_transform({
                                transform.basis,
                                transform.origin + registeredBody->shape_owner_get_transform(owner).origin
                            });

                            if (isEdition) {
                                Shape shape { *(registeredBody->shape_owner_get_shape(owner, j).ptr()) };
                                shape.set_margin(-0.1);
                                Ref<Shape> shapeRef = Ref<Shape>(&shape);
                                parameters->set_shape(shapeRef);
                            } else {
                                parameters->set_shape(registeredBody->shape_owner_get_shape(owner, j));
                            }

                            parameters->set_exclude(Array::make(registeredBody->get_rid()));
                            if (!physicsDirectSpaceState->intersect_shape(parameters, 1).empty()) return true;
                        }
                    }
                }
            }
        }
        return false;
    }

    template<class T>
    bool IsometricElement<T>::isCollidingAABB(bool isEdition) const {
        if (registeredBody) {
            const Vector3 &size {getSize3D()};
            const Vector3 &position {getPosition3D()};
            const Vector3 &convertedSize{size.x, size.z, size.y};
            PoolVector3Array poolVector3Array;
            Vector3 originPoint;
            poolVector3Array.push_back(originPoint);
            poolVector3Array.push_back({originPoint.x, originPoint.y, convertedSize.z});
            poolVector3Array.push_back({convertedSize.x, originPoint.y, originPoint.z});
            poolVector3Array.push_back({convertedSize.x,originPoint.y, convertedSize.z});
            poolVector3Array.push_back({originPoint.x, convertedSize.y, originPoint.z});
            poolVector3Array.push_back({originPoint.x, convertedSize.y, convertedSize.z});
            poolVector3Array.push_back({convertedSize.x, convertedSize.y, originPoint.z});
            poolVector3Array.push_back(convertedSize);
            ConvexPolygonShape *shape = ConvexPolygonShape::_new();
            shape->set_points(poolVector3Array);
            if (isEdition) {
                shape->set_margin(-0.1);
            }
            Ref<Shape> shapeRef = Ref<Shape>(shape);

            PhysicsShapeQueryParameters *parameters = PhysicsShapeQueryParameters::_new();
            parameters->set_shape(shapeRef);
            parameters->set_transform({
                {1, 0, 0, 0, 1, 0, 0, 0, 1},
                {position.x, position.z, position.y}
            });
            parameters->set_exclude(Array::make(registeredBody->get_rid()));
            return !registeredBody->get_world().ptr()->get_direct_space_state()->intersect_shape(parameters, 1).empty();
        }
        return false;
    }
}


#endif //ISOMETRICMAPEDITOR_ISOMETRICELEMENT_H
