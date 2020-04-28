#ifndef ISOMETRICMAPEDITOR_ISOMETRICPLACEHOLDER_H
#define ISOMETRICMAPEDITOR_ISOMETRICPLACEHOLDER_H

#include "IsometricPositionable.h"
#include "IsometricMap.h"
#include "PlaceholderType.h"

namespace godot {

    enum class SlopeType {NONE = 0, LEFT = 1, RIGHT = 2, FORWARD = 3, BACKWARD = 4};

    class IsometricPlaceholder : public IsometricPositionable {
        GODOT_SUBCLASS(IsometricPlaceholder, IsometricPositionable)

    private:
        Ref<PlaceholderType> placeholderType;
        SlopeType slopeType = SlopeType::NONE;

        float tempAlpha = 0.15;
        bool isSelected = false;

        PoolVector2Array debugPoints = PoolVector2Array();

        Color typeColor = Color(0.83, 0.83, 0.83, 1);
        PoolColorArray leftColor;
        PoolColorArray rightColor;
        PoolColorArray upColor;
        PoolColorArray downColor;
        PoolColorArray sideSlopeColor;
        PoolColorArray forwardSlopeColor;
        PoolColorArray backwardSlopeColor;
        PoolColorArray stairColor;

        Vector3 mapSize;

        void preparePoints();
        void drawPoints();
        void updateColors();

        void setMapSize(Vector3 size);
    public:
        static void _register_methods();

        void _init();
        void _draw();
        String getClass() const override;

        void _onGridUpdated(int stair) override;
        void _onSelect(bool selected) override;

        Ref<PlaceholderType> getPlaceholderType() const;
        void setPlaceholderType(Ref<PlaceholderType> pType);
        int getSlopeType();
        void setSlopeType(int type);
    };

}


#endif //ISOMETRICMAPEDITOR_ISOMETRICPLACEHOLDER_H
