#ifndef ISOMETRICMAPEDITOR_GRID3D_H
#define ISOMETRICMAPEDITOR_GRID3D_H


#include <core/Vector3.hpp>
#include <core/Variant.hpp>

namespace godot {
    class Grid3D {
    public:
        Grid3D();
        ~Grid3D();
        void updateArraySize(Vector3 size, bool reset = false);
        void setData(Vector3 position, Object *data);
        bool insertBox(AABB aabb, Object *data, bool remove = false);
    };
}


#endif //ISOMETRICMAPEDITOR_GRID3D_H
