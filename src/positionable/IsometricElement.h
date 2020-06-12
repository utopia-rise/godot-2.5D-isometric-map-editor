#ifndef ISOMETRICMAPEDITOR_ISOMETRICELEMENT_H
#define ISOMETRICMAPEDITOR_ISOMETRICELEMENT_H


#include <Godot.hpp>
#include <IsometricPositionable.h>

namespace godot {

    /**
     * Represents a 3D object that is a drawing unit, i.e. that is not a composition of other IsometricPositionable.
     */
    class IsometricElement : public IsometricPositionable {
        GODOT_SUBCLASS(IsometricElement, IsometricPositionable)

    private:
        SlopeType slopeType;

    protected:
        SlopeType
        calculateSlopeOffset(Vector2 *slopeOffset, real_t tileWidthFloat, real_t tileHeightFloat, real_t width,
                             real_t depth,
                             real_t ratio) const override;

    public:
        IsometricElement();
        ~IsometricElement() = default;

        static void _register_methods();

        void _init();
        String get_class() const override;

        /**
         * @return SlopeType of IsometricElement.
         */
        int getSlopeType();

        /**
         * Sets SlopeType of IsometricElement to `type` value.
         * @param type
         */
        void setSlopeType(int type);
    };

}


#endif //ISOMETRICMAPEDITOR_ISOMETRICELEMENT_H
