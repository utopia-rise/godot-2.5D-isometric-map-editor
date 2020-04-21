#ifndef ISOMETRICMAPEDITOR_GRID3D_H
#define ISOMETRICMAPEDITOR_GRID3D_H


#include <core/Vector3.hpp>
#include <core/Variant.hpp>
#include <gen/Reference.hpp>
#include <core/Godot.hpp>

namespace godot {
    class Grid3D {
    private:

#define ARRAY_SIZE width * depth * height

        int width = 1;
        int depth = 1;
        int height = 1;

        Array internalArray = Array();

        bool isInRange(int x, int y, int z) const;

        int getId(Vector3 position) const;
        Vector3 getPosition3D(int id) const;
        Vector3 planeSquareAndJumpsFrom(Vector3 size) const;

        static int indexIncrementFrom(Vector3 planeSquareAndJumps, Vector3 size, int iteration);
    public:
        Grid3D();
        ~Grid3D();

        void updateArraySize(Vector3 size, bool reset = false);
        void reset();
        Object *getData(Vector3 position);
        void setData(Vector3 position, Object *data);
        bool insertBox(AABB aabb, Object *data, bool remove = false);
        bool isOverlapping(AABB aabb) const;
        bool has(Object *object) const;

        void forEach(void (*fptr)(Object *));

        int getWidth() const;
        void setWidth(int w);
        int getDepth() const;
        void setDepth(int d);
        int getHeight() const;
        void setHeight(int h);

        Array getInternalArray();
        void setInternalArray(const Array& array);
    };
}


#endif //ISOMETRICMAPEDITOR_GRID3D_H
