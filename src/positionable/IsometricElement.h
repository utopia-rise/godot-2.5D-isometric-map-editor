#ifndef ISOMETRICMAPEDITOR_ISOMETRICELEMENT_H
#define ISOMETRICMAPEDITOR_ISOMETRICELEMENT_H

#include <IsometricPositionable.h>

namespace godot {

    template <class T>
    class IsometricElement : public IsometricPositionable {

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
        bool getHasDefaultBody() const;

        /**
         * Sets if StaticIsometricElement should have default body.
         * @param b
         */
        void setHasDefaultBody(bool b);

        bool getHasMoved() const;
        void setHasMoved(bool hm);

        virtual int getSlopeType() const;

        void setAABB(AABB ab) override;
        void setPosition3D(Vector3 pos) override;
        void onResize() override;
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
    bool IsometricElement<T>::getHasMoved() const {
        return hasMoved;
    }

    template<class T>
    void IsometricElement<T>::setHasMoved(bool hm) {
        hasMoved = hm;
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
    String IsometricElement<T>::get_class() const {
        return "IsometricElement";
    }
}


#endif //ISOMETRICMAPEDITOR_ISOMETRICELEMENT_H
