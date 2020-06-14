#ifndef ISOMETRICMAPEDITOR_STATICISOMETRICELEMENT_H
#define ISOMETRICMAPEDITOR_STATICISOMETRICELEMENT_H

#include <positionable/physics/DefaultStaticBody.h>

namespace godot {

    /**
     * IsometricElement that cannot move. IE, no position control on it in game.
     */
    class StaticIsometricElement : public IsometricPositionable {
        GODOT_SUBCLASS(StaticIsometricElement, IsometricPositionable)

    private:
        bool hasDefaultBody;
        DefaultStaticBody *defaultBody;

        SlopeType slopeType;

        /**
         * Sets or remove defaultBody in function of hasDefaultBody
         */
        void updateDefaultBody();

    protected:
        SlopeType
        calculateSlopeOffset(Vector2 *slopeOffset, real_t tileWidthFloat, real_t tileHeightFloat, real_t width,
                             real_t depth,
                             real_t ratio) const override;

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

        int getSlopeType();
        void setSlopeType(int type);

        void setAABB(AABB ab) override;
        void setPosition3D(Vector3 pos) override;
    };
}

#endif //ISOMETRICMAPEDITOR_STATICISOMETRICELEMENT_H