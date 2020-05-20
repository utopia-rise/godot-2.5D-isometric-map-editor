#ifndef ISOMETRICMAPEDITOR_OUTLINEDRAWER_H
#define ISOMETRICMAPEDITOR_OUTLINEDRAWER_H


#include <Godot.hpp>
#include <gen/Node2D.hpp>

namespace godot {

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
        void setPoints(PoolVector2Array *up, PoolVector2Array *down);
        void setColor(const Color &c);
        const Color &getColor() const;
        void setLineSize(real_t size);
        real_t getLineSize() const;
    };

}


#endif //ISOMETRICMAPEDITOR_OUTLINEDRAWER_H
