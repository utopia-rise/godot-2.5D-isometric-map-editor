#ifndef ISOMETRICMAPEDITOR_STATICISOMETRICELEMENT_H
#define ISOMETRICMAPEDITOR_STATICISOMETRICELEMENT_H

#include <positionable/physics/DefaultStaticBody.h>
#include <IsometricElement.h>

namespace godot {

    /**
     * IsometricElement that cannot move. IE, no position control on it in game.
     */
    class StaticIsometricElement : public IsometricElement<DefaultStaticBody> {
        GODOT_SUBCLASS(StaticIsometricElement, IsometricElement)

    private:
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
         * Sets if StaticIsometricElement should have default body.
         * @param b
         */
        void setHasDefaultBody(bool b) override;

        int getSlopeType() const override;
        void setSlopeType(int type);

        void setAABB(AABB ab) override;
        void setPosition3D(Vector3 pos) override;

        void onResize() override;
    };
}

#endif //ISOMETRICMAPEDITOR_STATICISOMETRICELEMENT_H