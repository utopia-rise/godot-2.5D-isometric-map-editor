#ifndef ISOMETRICMAPEDITOR_MATHHELPER_H
#define ISOMETRICMAPEDITOR_MATHHELPER_H

namespace godot {

    inline constexpr double deg2rad(float deg) {
        return deg / 180.0 * Math_PI;
    }

    inline constexpr int clamp(int value, int min, int max) {
        return value < min ? min : (value > max ? max : value);
    }

    inline constexpr real_t min(real_t val1, real_t val2) {
        return val1 < val2 ? val1 : val2;
    }
}

#endif //ISOMETRICMAPEDITOR_MATHHELPER_H
