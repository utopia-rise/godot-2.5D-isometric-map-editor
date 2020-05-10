#include <OutlineDrawer.h>

using namespace godot;

void OutlineDrawer::_register_methods() {
    register_method("_init", &OutlineDrawer::_init);
    register_method("_draw", &OutlineDrawer::_draw);
}

OutlineDrawer::OutlineDrawer() : upPoints(nullptr), downPoints(nullptr) {

}

void OutlineDrawer::_init() {
    set_z_index(4096);
}

void OutlineDrawer::_draw() {
//    Upper Lines
    const Color &colorRed { Color(255, 0, 0, 1) };
    constexpr real_t lineSize { 10.0f };
    PoolVector2Array upP = *upPoints;
    draw_line(upP[0], upP[1], colorRed, lineSize);
    draw_line(upP[1], upP[2], colorRed, lineSize);
    draw_line(upP[2], upP[3], colorRed, lineSize);
    draw_line(upP[3], upP[0], colorRed, lineSize);

//    Vertical Lines
    PoolVector2Array downP = *downPoints;
    draw_line(upP[0], downP[0], colorRed, lineSize);
    draw_line(upP[1], downP[1], colorRed, lineSize);
    draw_line(upP[2], downP[2], colorRed, lineSize);
    draw_line(upP[3], downP[3], colorRed, lineSize);

//    Lower Lines
    draw_line(downP[0], downP[1], colorRed, lineSize);
    draw_line(downP[1], downP[2], colorRed, lineSize);
    draw_line(downP[2], downP[3], colorRed, lineSize);
    draw_line(downP[3], downP[0], colorRed, lineSize);
}

void OutlineDrawer::setPoints(PoolVector2Array *up, PoolVector2Array *down) {
    upPoints = up;
    downPoints = down;
}
