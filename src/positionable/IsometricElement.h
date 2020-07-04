#ifndef ISOMETRICMAPEDITOR_ISOMETRICELEMENT_H
#define ISOMETRICMAPEDITOR_ISOMETRICELEMENT_H

#include <Godot.hpp>
#include <IsometricPositionable.h>
#include <gen/PhysicsServer.hpp>
#include <gen/World.hpp>
#include <gen/PhysicsDirectSpaceState.hpp>
#include <gen/PhysicsShapeQueryParameters.hpp>

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

        PhysicsBody *getRegisteredBody() const;
        void setRegisteredBody(PhysicsBody *physicsBody);

        virtual void updatePositionFromBody(PhysicsBody *physicsBody);

        virtual int getSlopeType() const;

        void setAABB(AABB ab) override;
        void setPosition3D(Vector3 pos) override;
        void onResize() override;

        bool getHasMoved() const override;
        void setHasMoved(bool hm) override;
        bool isColliding() const override;
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
    bool IsometricElement<T>::isColliding() const {
        if (registeredBody) {
            Ref<World> world = registeredBody->get_world();
            if (world.is_valid()) {
                PhysicsDirectSpaceState *physicsDirectSpaceState = world.ptr()->get_direct_space_state();
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
                        parameters->set_shape(registeredBody->shape_owner_get_shape(owner, j));
                        parameters->set_exclude(Array::make(registeredBody->get_rid()));
                        if (!physicsDirectSpaceState->intersect_shape(parameters).empty()) return true;
                    }
                }
            }
        }
        return false;
    }
}


#endif //ISOMETRICMAPEDITOR_ISOMETRICELEMENT_H
