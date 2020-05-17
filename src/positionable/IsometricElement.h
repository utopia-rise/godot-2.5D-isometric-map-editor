#ifndef ISOMETRICMAPEDITOR_ISOMETRICELEMENT_H
#define ISOMETRICMAPEDITOR_ISOMETRICELEMENT_H


#include <Godot.hpp>
#include <IsometricPositionable.h>

namespace godot {

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

        int getSlopeType();
        void setSlopeType(int type);
    };

}


#endif //ISOMETRICMAPEDITOR_ISOMETRICELEMENT_H
