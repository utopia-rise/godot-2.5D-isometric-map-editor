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

    public:
        OutlineDrawer();
        ~OutlineDrawer() = default;

        static void _register_methods();

        void _init();
        void _draw();
        void setPointsAndColor(PoolVector2Array *up, PoolVector2Array *down, const Color &c);
    };

}


#endif //ISOMETRICMAPEDITOR_OUTLINEDRAWER_H
