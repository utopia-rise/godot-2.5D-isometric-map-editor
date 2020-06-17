#ifndef ISOMETRICMAPEDITOR_ISOMETRICELEMENT_H
#define ISOMETRICMAPEDITOR_ISOMETRICELEMENT_H

#include <IsometricPositionable.h>

namespace godot {

    template <class T>
    class IsometricElement : public IsometricPositionable {
        GODOT_SUBCLASS(IsometricElement, IsometricPositionable)

    protected:
        bool hasMoved;
        bool hasDefaultBody;
        T *defaultBody;

    public:
        IsometricElement();
        ~IsometricElement() = default;

        static void _register_methods();

        void _init();

        /**
         * @return true if should have default body.
         */
        bool getHasDefaultBody() const;

        /**
         * Sets if StaticIsometricElement should have default body.
         * @param b
         */
        virtual void setHasDefaultBody(bool b);

        bool getHasMoved() const;
        void setHasMoved(bool hm);

        virtual int getSlopeType() const;
    };

    template<class T>
    IsometricElement<T>::IsometricElement(): hasMoved(false), hasDefaultBody(true), defaultBody(nullptr) {

    }

    template<class T>
    void IsometricElement<T>::_register_methods() {
        register_property("has_default_body", &IsometricElement::setHasDefaultBody, &IsometricElement::getHasDefaultBody,
                          true);
    }

    template<class T>
    void IsometricElement<T>::_init() {
        IsometricPositionable::_init();
    }

    template<class T>
    bool IsometricElement<T>::getHasDefaultBody() const {
        return hasDefaultBody;
    }

    template<class T>
    void IsometricElement<T>::setHasDefaultBody(bool b) {
        hasDefaultBody = b;
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
}


#endif //ISOMETRICMAPEDITOR_ISOMETRICELEMENT_H
