#ifndef ISOMETRICMAPEDITOR_ISOMETRICPLACEHOLDER_H
#define ISOMETRICMAPEDITOR_ISOMETRICPLACEHOLDER_H

#include <IsometricPositionable.h>
#include <IsometricMap.h>
#include <PlaceholderType.h>
#include "IsometricElement.h"

namespace godot {

    /**
     * IsometricElement to design maps without having the assets yet.
     * A PlaceholderType resource can be provided to set color according to what placeholder represents.
     * Should be used for development and prototyping only.
     */
    class IsometricPlaceholder : public IsometricElement {
        GODOT_SUBCLASS(IsometricPlaceholder, IsometricElement)

    private:
        Ref<PlaceholderType> placeholderType;

        float tempAlpha = 0.15;

        PoolColorArray leftColor;
        PoolColorArray rightColor;
        PoolColorArray upColor;
        PoolColorArray downColor;
        PoolColorArray sideSlopeColor;
        PoolColorArray forwardSlopeColor;
        PoolColorArray backwardSlopeColor;
        PoolColorArray stairColor;

        Vector3 mapSize;

        /**
         * Draw the placeholder using prepared points by IsometricPositionable::preparePoints
         * @see IsometricPositionable::preparePoints
         */
        void drawPoints();

        /**
         * Update colors of placeholder sides using PlaceholderType resource.
         */
        void updateColors();

        /**
         * @deprecated
         * @param size
         */
        void setMapSize(const Vector3 &size);
    public:
        IsometricPlaceholder() = default;
        ~IsometricPlaceholder() = default;

        static void _register_methods();

        void _init();
        void _draw();
        String get_class() const override;

        void _onGridUpdated(int stair) override;
        void _onResize() override;

        /**
         * @return PlaceholderType of placeholder.
         */
        Ref<PlaceholderType> getPlaceholderType() const;

        /**
         * Sets type of placeholder.
         * @param pType
         */
        void setPlaceholderType(Ref<PlaceholderType> pType);
    };

}


#endif //ISOMETRICMAPEDITOR_ISOMETRICPLACEHOLDER_H
