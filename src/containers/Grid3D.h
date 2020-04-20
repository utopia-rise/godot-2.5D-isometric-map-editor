#ifndef ISOMETRICMAPEDITOR_GRID3D_H
#define ISOMETRICMAPEDITOR_GRID3D_H


#include <core/Vector3.hpp>
#include <core/Variant.hpp>

namespace godot {
    class Grid3D {
    private:

#define ARRAY_SIZE width * depth * height

        int width = 1;
        int depth = 1;
        int height = 1;

        Array internalArray = Array();

        bool isInRange(int x, int y, int z);

        Vector3 getPosition3D(int id);
    public:
        Grid3D();
        ~Grid3D();

        void updateArraySize(Vector3 size, bool reset = false);
        void reset();
        Object *getData(Vector3 position);
        void setData(Vector3 position, Object *data);
        bool insertBox(AABB aabb, Object *data, bool remove = false);
        bool isOverlapping(AABB aabb);

        void forEach(void (*fptr)(Object *));

        int getWidth();
        void setWidth(int w);
        int getDepth();
        void setDepth(int d);
        int getHeight();
        void setHeight(int h);

        Array getInternalArray();
        void setInternalArray(Array array);
    };
}


#endif //ISOMETRICMAPEDITOR_GRID3D_H
