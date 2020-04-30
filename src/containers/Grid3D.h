#ifndef ISOMETRICMAPEDITOR_GRID3D_H
#define ISOMETRICMAPEDITOR_GRID3D_H


#include <core/Vector3.hpp>
#include <core/Variant.hpp>
#include <gen/Reference.hpp>
#include <core/Godot.hpp>

namespace godot {
    class Grid3D {
    private:

        int width = 1;
        int depth = 1;
        int height = 1;

        Array internalArray;

        bool isInRange(int x, int y, int z) const;

        int getId(const Vector3 &position) const;
        Vector3 getPosition3D(int id) const;
        Vector3 planeSquareAndJumpsFrom(const Vector3 &size) const;

        inline int computeArraySize() const {
            return width * depth * height;
        }

        static int indexIncrementFrom(const Vector3 &planeSquareAndJumps, const Vector3 &size, int iteration);
    public:
        Grid3D() = default;
        ~Grid3D() = default;

        void updateArraySize(const Vector3 &size, bool reset = false);
        void reset();
        Object *getData(const Vector3 &position);
        void setData(const Vector3 &position, Object *data);
        bool insertBox(const AABB &aabb, Object *data, bool remove = false);
        bool isOverlapping(const AABB &aabb) const;
        bool has(Object *object) const;

        void forEach(void (*fptr)(Object *));

        int getWidth() const;
        void setWidth(int w);
        int getDepth() const;
        void setDepth(int d);
        int getHeight() const;
        void setHeight(int h);

        const Array &getInternalArray() const;
        void setInternalArray(const Array& array);
    };
}


#endif //ISOMETRICMAPEDITOR_GRID3D_H
