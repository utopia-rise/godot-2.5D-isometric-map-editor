#ifndef ISOMETRICMAPEDITOR_ISOMETRICPLACEHOLDER_H
#define ISOMETRICMAPEDITOR_ISOMETRICPLACEHOLDER_H

#include <IsometricPositionable.h>
#include <IsometricMap.h>
#include <PlaceholderType.h>

namespace godot {

    class IsometricPlaceholder : public IsometricPositionable {
        GODOT_SUBCLASS(IsometricPlaceholder, IsometricPositionable)

    private:
        Ref<PlaceholderType> placeholderType;

        float tempAlpha = 0.15;

        Color typeColor;
        PoolColorArray leftColor;
        PoolColorArray rightColor;
        PoolColorArray upColor;
        PoolColorArray downColor;
        PoolColorArray sideSlopeColor;
        PoolColorArray forwardSlopeColor;
        PoolColorArray backwardSlopeColor;
        PoolColorArray stairColor;

        Vector3 mapSize;

        void drawPoints();
        void updateColors();

        void setMapSize(const Vector3 &size);
    public:
        IsometricPlaceholder();
        ~IsometricPlaceholder() = default;

        static void _register_methods();

        void _init();
        void _draw();
        String get_class() const override;

        void _onGridUpdated(int stair) override;
        void _onResize() override;

        Ref<PlaceholderType> getPlaceholderType() const;
        void setPlaceholderType(Ref<PlaceholderType> pType);
    };

}


#endif //ISOMETRICMAPEDITOR_ISOMETRICPLACEHOLDER_H
