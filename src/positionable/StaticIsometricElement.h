#ifndef ISOMETRICMAPEDITOR_STATICISOMETRICELEMENT_H
#define ISOMETRICMAPEDITOR_STATICISOMETRICELEMENT_H

#include <IsometricElement.h>
#include <positionable/physics/DefaultStaticBody.h>

namespace godot {

    /**
     * IsometricElement that cannot move. IE, no position control on it in game.
     */
    class StaticIsometricElement : public IsometricElement {
        GODOT_SUBCLASS(StaticIsometricElement, IsometricElement)

    private:
        bool hasDefaultBody;
        DefaultStaticBody *defaultBody;

        /**
         * Sets or remove defaultBody in function of hasDefaultBody
         */
        void updateDefaultBody();
    public:
        StaticIsometricElement();
        ~StaticIsometricElement() = default;

        static void _register_methods();

        void _init();
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

        void setAABB(AABB ab) override;
        void setPosition3D(Vector3 pos) override;
    };
}

#endif //ISOMETRICMAPEDITOR_STATICISOMETRICELEMENT_H