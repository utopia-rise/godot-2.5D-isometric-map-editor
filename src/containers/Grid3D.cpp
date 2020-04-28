#include "Grid3D.h"

using namespace godot;

Grid3D::Grid3D() = default;
Grid3D::~Grid3D() = default;

void Grid3D::updateArraySize(godot::Vector3 size, bool reset) {
    //Save old values
    int oldSize = internalArray.size();
    Array oldArray = internalArray;
    int oldWidth = width;
    int oldDepth = depth;

    //Set new values
    width = (int) size.x;
    depth = (int) size.y;
    height = (int) size.z;
    internalArray = Array();

    for (int i = 0; i < ARRAY_SIZE; i++) {
        internalArray.append((Object *) nullptr);
    }

    if (reset) {
        return;
    }

    for (int i = 0; i < oldSize; i++) {
        int x = i % oldWidth;
        int y = (i / oldWidth) % oldDepth;
        int z = i / (oldWidth * oldDepth);

        if (!isInRange(x, y, z)) {
            continue;
        }

        Object *value = oldArray[i];
        if (value) {
            setData({(real_t) x, (real_t) y, (real_t) z}, value);
        }
    }
}

void Grid3D::reset() {
    updateArraySize({(real_t) width, (real_t) depth, (real_t) height}, true);
}

Object *Grid3D::getData(Vector3 position) {
    return (int) position.x >= 0 && (int) position.x < width && (int) position.y >= 0 && (int) position.y < depth && (int) position.z >= 0 && (int) position.z < height
    ? (Object *) internalArray[(int) position.x + width * (int) position.y + width * depth * (int) position.z]
    : nullptr;
}

void Grid3D::setData(Vector3 position, Object *data) {
    internalArray[(int) position.x + width * (int) position.y + width * depth * (int) position.z] = data;
}

bool Grid3D::insertBox(AABB aabb, Object *data, bool remove) {
    Vector3 position = aabb.position;
    Vector3 size = aabb.size;
    int index = getId(position);
    int endX = (int) position.x + (int) size.x;
    int endY = (int) position.y + (int) size.y;
    int endZ = (int) position.z + (int) size.z;

    if (endX > width || endY > depth || endZ > height) {
        return false;
    }

    internalArray[index] = remove ? nullptr : data;
    for (int i = 1; i < (int) size.x * (int) size.y * (int) size.z; i++) {
        index += Grid3D::indexIncrementFrom(planeSquareAndJumpsFrom(size), size, i);
        internalArray[index] = remove ? nullptr : data;
    }
    return true;
}

bool Grid3D::isOverlapping(AABB aabb) const {
    int index = getId(aabb.position);
    Vector3 size = aabb.size;

    if (index >= 0 && index < internalArray.size()) {
        Object *element = internalArray[index];
        if (element) {
            return true;
        }
        for (int i = 1; i < (int) size.x * (int) size.y * (int) size.z; i++) {
            index += Grid3D::indexIncrementFrom(planeSquareAndJumpsFrom(size), size, i);
            element = internalArray[index];
            if (element) {
                return true;
            }
        }
    }
    return false;
}

bool Grid3D::has(Object *object) const {
    for (int i = 0; i < internalArray.size(); i++) {
        if ((Object *) internalArray[i] == object) {
            return true;
        }
    }
    return false;
}

int Grid3D::getWidth() const {
    return width;
}

void Grid3D::setWidth(int w) {
    updateArraySize({
        (real_t) w,
        (real_t) depth,
        (real_t) height
    });
}

int Grid3D::getDepth() const {
    return depth;
}

void Grid3D::setDepth(int d) {
    updateArraySize({
        (real_t) width,
        (real_t) d,
        (real_t) height
    });
}

int Grid3D::getHeight() const {
    return height;
}

void Grid3D::setHeight(int h) {
    updateArraySize({
        (real_t) width,
        (real_t) depth,
        (real_t) h
    });
}

Array Grid3D::getInternalArray() {
    return internalArray;
}

void Grid3D::setInternalArray(const Array& array) {
    internalArray = array;
}

void Grid3D::forEach(void (*fptr)(Object *)) {
    for (int i = 0; i < internalArray.size(); i++) {
        Object *element = internalArray[i];
        if (element) {
            fptr(element);
        }
    }
}

bool Grid3D::isInRange(int x, int y, int z) const {
    return x < width && y < depth && z < height;
}

int Grid3D::getId(Vector3 position) const {
    return (int) position.x + width * (int) position.y + width * depth * (int) position.z;
}

Vector3 Grid3D::getPosition3D(int id) const {
    return {
        (real_t) (id % width),
        (real_t) ((id / width) % depth),
        (real_t) id / ((real_t) width * (real_t) depth)
    };
}

Vector3 Grid3D::planeSquareAndJumpsFrom(Vector3 size) const {
    return {
        size.x * size.y,
        (real_t ) width - size.x,
        (real_t ) width * ((float) depth - size.y)
    };
}

int Grid3D::indexIncrementFrom(Vector3 planeSquareAndJumps, Vector3 size, int iteration) {
    int increment = 0;
    increment += (iteration % (int) size.x) == 0 ? (int) planeSquareAndJumps.y : 0;
    increment += (iteration % (int) planeSquareAndJumps.x) == 0 ? (int) planeSquareAndJumps.z : 0;
    increment += 1;
    return increment;
}