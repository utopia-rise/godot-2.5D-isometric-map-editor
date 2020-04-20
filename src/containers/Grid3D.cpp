//
// Created by piertho on 19/04/2020.
//

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
    int oldHeight = height;

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
    return position.x >= 0 && position.x < width && position.y >= 0 && position.y < depth && position.z >= 0 && position.z < height
    ? (Object *) internalArray[(int) position.x + width * (int) position.y + width * depth * (int) position.z]
    : nullptr;
}

void Grid3D::setData(Vector3 position, Object *data) {
    internalArray[(int) position.x + width * (int) position.y + width * depth * (int) position.z] = data;
}

bool Grid3D::insertBox(AABB aabb, Object *data, bool remove) {
    //TODO
    return false;
}

bool Grid3D::isOverlapping(AABB aabb) {
    //TODO
    return false;
}

int Grid3D::getWidth() {
    return width;
}

void Grid3D::setWidth(int w) {
    updateArraySize({
        (real_t) w,
        (real_t) depth,
        (real_t) height
    });
}

int Grid3D::getDepth() {
    return depth;
}

void Grid3D::setDepth(int d) {
    updateArraySize({
        (real_t) width,
        (real_t) d,
        (real_t) height
    });
}

int Grid3D::getHeight() {
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

void Grid3D::setInternalArray(Array array) {
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

bool Grid3D::isInRange(int x, int y, int z) {
    return x < width && y < depth && z < height;
}

Vector3 Grid3D::getPosition3D(int id) {
    return {
        (real_t) (id % width),
        (real_t) ((id / width) % depth),
        (real_t) id / (width * depth)
    };
}
