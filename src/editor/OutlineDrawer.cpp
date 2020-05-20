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
    PoolVector2Array upP = *upPoints;
    draw_line(upP[0], upP[1], color, lineSize);
    draw_line(upP[1], upP[2], color, lineSize);
    draw_line(upP[2], upP[3], color, lineSize);
    draw_line(upP[3], upP[0], color, lineSize);

//    Vertical Lines
    PoolVector2Array downP = *downPoints;
    draw_line(upP[0], downP[0], color, lineSize);
    draw_line(upP[1], downP[1], color, lineSize);
    draw_line(upP[2], downP[2], color, lineSize);
    draw_line(upP[3], downP[3], color, lineSize);

//    Lower Lines
    draw_line(downP[0], downP[1], color, lineSize);
    draw_line(downP[1], downP[2], color, lineSize);
    draw_line(downP[2], downP[3], color, lineSize);
    draw_line(downP[3], downP[0], color, lineSize);
}

void OutlineDrawer::setPoints(PoolVector2Array *up, PoolVector2Array *down) {
    upPoints = up;
    downPoints = down;
}

void OutlineDrawer::setColor(const Color &c) {
    color = c;
}

const Color &OutlineDrawer::getColor() const {
    return color;
}

void OutlineDrawer::setLineSize(real_t size) {
    lineSize = size;
}

real_t OutlineDrawer::getLineSize() const {
    return lineSize;
}
