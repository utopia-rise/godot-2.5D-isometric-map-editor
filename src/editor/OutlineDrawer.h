#ifndef ISOMETRICMAPEDITOR_OUTLINEDRAWER_H
#define ISOMETRICMAPEDITOR_OUTLINEDRAWER_H


#include <Godot.hpp>
#include <gen/Node2D.hpp>

namespace godot {

    /**
     * Used in editor.
     * It prints the outline of a positionable when selected in map edition mode.
     * Also prints outline when editing IsometricTile.
     */
    class OutlineDrawer : public Node2D {
        GODOT_CLASS(OutlineDrawer, Node2D)

    private:
        PoolVector2Array *upPoints;
        PoolVector2Array *downPoints;
        Color color;
        real_t lineSize;

    public:
        OutlineDrawer();
        ~OutlineDrawer() = default;

        static void _register_methods();

        void _init();
        void _draw();

        /**
         * Set points to calculate lines to draw.
         * @param up
         * @param down
         */
        void setPoints(PoolVector2Array *up, PoolVector2Array *down);

        /**
         * Set color of lines to draw.
         * @param c
         */
        void setColor(const Color &c);

        /**
         * @return colors of lines.
         */
        const Color &getColor() const;

        /**
         * Set line thickness.
         * @param size
         */
        void setLineSize(real_t size);

        /**
         * @return line thickness.
         */
        real_t getLineSize() const;
    };

}


#endif //ISOMETRICMAPEDITOR_OUTLINEDRAWER_H
