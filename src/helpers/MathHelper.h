#ifndef ISOMETRICMAPEDITOR_MATHHELPER_H
#define ISOMETRICMAPEDITOR_MATHHELPER_H

namespace godot {

#define DEG2RAD(deg) deg / 180 * Math_PI
#define CLAMP(value, min, max) value < min ? min : (value > max ? max : value)
#define CEIL(value) (int) value + 1
#define MIN(val1, val2) val1 < val2 ? val1 : val2

}

#endif //ISOMETRICMAPEDITOR_MATHHELPER_H
