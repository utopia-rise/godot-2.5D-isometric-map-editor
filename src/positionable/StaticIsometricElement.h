#ifndef ISOMETRICMAPEDITOR_STATICISOMETRICELEMENT_H
#define ISOMETRICMAPEDITOR_STATICISOMETRICELEMENT_H

#include <IsometricElement.h>
#include <gen/StaticBody.hpp>

namespace godot {

    class StaticIsometricElement : public IsometricElement {
        GODOT_SUBCLASS(StaticIsometricElement, IsometricElement)

    private:
        StaticBody *defaultBody;

    public:
        StaticIsometricElement();
        ~StaticIsometricElement() = default;

        static void _register_methods();

        void _init();
        String get_class() const override;

        /**
         * @return true if has default body.
         */
        bool hasDefaultBody() const;

        /**
         * Sets default body if `b` is true. Otherwise it will remove defaultBody if exists.
         * @param b
         */
        void setDefaultBody(bool b);
    };
}

#endif //ISOMETRICMAPEDITOR_STATICISOMETRICELEMENT_H