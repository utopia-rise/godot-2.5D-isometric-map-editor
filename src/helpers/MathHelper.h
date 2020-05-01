#ifndef ISOMETRICMAPEDITOR_MATHHELPER_H
#define ISOMETRICMAPEDITOR_MATHHELPER_H

namespace godot {

    inline constexpr float deg2rad(float deg) {
        return deg / 180.f * static_cast<float>(Math_PI);
    }

    inline constexpr int clamp(int value, int min, int max) {
        return value < min ? min : (value > max ? max : value);
    }

    inline constexpr int ceil(float value) {
        return static_cast<int>(value) + 1;
    }

    inline constexpr real_t min(real_t val1, real_t val2) {
        return val1 < val2 ? val1 : val2;
    }
}

#endif //ISOMETRICMAPEDITOR_MATHHELPER_H
