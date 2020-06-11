#ifndef ISOMETRICMAPEDITOR_GRID3D_H
#define ISOMETRICMAPEDITOR_GRID3D_H


#include <core/Vector3.hpp>
#include <core/Variant.hpp>
#include <gen/Reference.hpp>
#include <core/Godot.hpp>

namespace godot {

    /**
     * Linearized 3D array of Variant.
     * Use AABB to handle 3D position and size of the object in order to place it in array.
     */
    class Grid3D {
    private:

        int width = 1;
        int depth = 1;
        int height = 1;

        Array internalArray;

        /**
         * @param x
         * @param y
         * @param z
         * @return true if `x`, `y`  and `z` corresponds to a position in the map.
         */
        bool isInRange(int x, int y, int z) const;

        /**
         * @param position
         * @return position in array using Vector3 `position`.
         */
        int getId(const Vector3 &position) const;

        /**
         * @param id
         * @return 3D position corresponding to position in array `id`.
         */
        Vector3 getPosition3D(int id) const;

        /**
         * @param size
         * @return a Vector3 composed of the size of lower/upper face, the jump on x for insert in linearized array
         * and jump on y for insert in linearized array
         */
        Vector3 planeSquareAndJumpsFrom(const Vector3 &size) const;

        /**
         * @return size of the linear array.
         */
        inline int computeArraySize() const {
            return width * depth * height;
        }

        /**
         * @param planeSquareAndJumps
         * @param size
         * @param iteration
         * @return increment for inserting element using result of godot::Grid3D::planeSquareAndJumpsFrom, size of
         * element and the iteration number.
         */
        static int indexIncrementFrom(const Vector3 &planeSquareAndJumps, const Vector3 &size, int iteration);
    public:
        Grid3D() = default;
        ~Grid3D() = default;

        /**
         * Resize linear array to corresponding 3D `size`.
         * Remove all elements if `reset` is true.
         * @param size
         * @param reset
         */
        void updateArraySize(const Vector3 &size, bool reset = false);

        /**
         * Clear content of Grid3D.
         */
        void reset();

        /**
         * @param position
         * @return the `Object` at 3D `position`.
         */
        Object *getData(const Vector3 &position);

        /**
         * Inserts `Object` to 3D `position` (Without taking care of the size).
         * Do nothing if an object is already here.
         * @param position
         * @param data
         */
        void setData(const Vector3 &position, Object *data);

        /**
         * Inserts `Object` in the Grid3D in each position it fills if `remove` is false.
         * Remove objects for each positions the `aabb` fills if `remove` is true.
         * @param aabb
         * @param data
         * @param remove
         * @return
         */
        bool insertBox(const AABB &aabb, Object *data, bool remove = false);

        /**
         * @param aabb
         * @return true if AABB 3D overlaps an element of the array.
         */
        bool isOverlapping(const AABB &aabb) const;

        /**
         * @param object
         * @return true if this Grid3D contains `object`.
         */
        bool has(Object *object) const;

        /**
         * Execute a function for each element of this Grid3D.
         * @param fptr
         */
        void forEach(void (*fptr)(Object *));

        /**
         * @return the width of this Grid3D
         */
        int getWidth() const;

        /**
         * Set the width of this Grid3D
         * @param w
         */
        void setWidth(int w);

        /**
         * @return the depth of this Grid3D
         */
        int getDepth() const;

        /**
         * Set the depth of this Grid3D
         * @param w
         */
        void setDepth(int d);

        /**
         * @return the height of this Grid3D
         */
        int getHeight() const;

        /**
         * Set the height of this Grid3D
         * @param w
         */
        void setHeight(int h);

        /**
         * @return a reference to the linear array. (Use carefully)
         */
        const Array &getInternalArray() const;

        /**
         * Force set the internal array. (Use carefully)
         * @param array
         */
        void setInternalArray(const Array& array);
    };
}


#endif //ISOMETRICMAPEDITOR_GRID3D_H
