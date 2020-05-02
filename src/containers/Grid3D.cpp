#include <Grid3D.h>

using namespace godot;

void Grid3D::updateArraySize(const Vector3 &size, bool reset) {
    //Save old values
    int oldSize { internalArray.size() };
    Array oldArray { internalArray };
    int oldWidth { width };
    int oldDepth { depth };

    //Set new values
    width = static_cast<int>(size.x);
    depth = static_cast<int>(size.y);
    height = static_cast<int>(size.z);
    internalArray = Array();

    for (int i = 0; i < computeArraySize(); i++) {
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
            setData({static_cast<real_t>(x), static_cast<real_t>(y), static_cast<real_t>(z)}, value);
        }
    }
}

void Grid3D::reset() {
    updateArraySize({static_cast<real_t>(width), static_cast<real_t>(depth), static_cast<real_t>(height)}, true);
}

Object *Grid3D::getData(const Vector3 &position) {
    int posX = static_cast<int>(position.x);
    int posY = static_cast<int>(position.y);
    int posZ = static_cast<int>(position.z);
    return posX >= 0 && posX < width && posY >= 0 && posY < depth && posZ >= 0 && posZ < height
    ? (Object *) internalArray[posX + width * posY + width * depth * posZ]
    : nullptr;
}

void Grid3D::setData(const Vector3 &position, Object *data) {
    internalArray[static_cast<int>(position.x) + width * static_cast<int>(position.y) + width * depth * static_cast<int>(position.z)] = data;
}

bool Grid3D::insertBox(const AABB &aabb, Object *data, bool remove) {
    const Vector3 &position { aabb.position };
    const Vector3 &size { aabb.size };
    int index { getId(position) };
    int sizeX = static_cast<int>(size.x);
    int sizeY = static_cast<int>(size.y);
    int sizeZ = static_cast<int>(size.z);
    int endX = static_cast<int>(position.x) + sizeX;
    int endY = static_cast<int>(position.y) + sizeY;
    int endZ = static_cast<int>(position.z) + sizeZ;

    if (endX > width || endY > depth || endZ > height) {
        return false;
    }

    internalArray[index] = remove ? nullptr : data;
    for (int i = 1; i < sizeX * sizeY * sizeZ; i++) {
        index += Grid3D::indexIncrementFrom(planeSquareAndJumpsFrom(size), size, i);
        internalArray[index] = remove ? nullptr : data;
    }
    return true;
}

bool Grid3D::isOverlapping(const AABB &aabb) const {
    int index { getId(aabb.position) };
    const Vector3 &size { aabb.size };

    if (index >= 0 && index < internalArray.size()) {
        Object *element = internalArray[index];
        if (element) {
            return true;
        }
        for (int i = 1; i < static_cast<int>(size.x) * static_cast<int>(size.y) * static_cast<int>(size.z); i++) {
            index += Grid3D::indexIncrementFrom(planeSquareAndJumpsFrom(size), size, i);
            if (index >= 0 && index < internalArray.size()) {
                element = internalArray[index];
                if (element) {
                    return true;
                }
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
        static_cast<real_t>(w),
        static_cast<real_t>(depth),
        static_cast<real_t>(height)
    });
}

int Grid3D::getDepth() const {
    return depth;
}

void Grid3D::setDepth(int d) {
    updateArraySize({
        static_cast<real_t>(width),
        static_cast<real_t>(d),
        static_cast<real_t>(height)
    });
}

int Grid3D::getHeight() const {
    return height;
}

void Grid3D::setHeight(int h) {
    updateArraySize({
        static_cast<real_t>(width),
        static_cast<real_t>(depth),
        static_cast<real_t>(h)
    });
}

const Array &Grid3D::getInternalArray() const {
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

int Grid3D::getId(const Vector3 &position) const {
    return static_cast<int>(position.x) + width * static_cast<int>(position.y) + width * depth * static_cast<int>(position.z);
}

Vector3 Grid3D::getPosition3D(int id) const {
    return {
            static_cast<real_t>(id % width),
            static_cast<real_t>((id / width) % depth),
            static_cast<real_t>(id) / (width * depth)
    };
}

Vector3 Grid3D::planeSquareAndJumpsFrom(const Vector3 &size) const {
    return {
        size.x * size.y,
        static_cast<real_t>(width) - size.x,
        width * (depth - size.y)
    };
}

int Grid3D::indexIncrementFrom(const Vector3 &planeSquareAndJumps, const Vector3 &size, int iteration) {
    int increment { 0 };
    increment += (iteration % static_cast<int>(size.x)) == 0 ? static_cast<int>(planeSquareAndJumps.y) : 0;
    increment += (iteration % static_cast<int>(planeSquareAndJumps.x)) == 0 ? static_cast<int>(planeSquareAndJumps.z) : 0;
    increment += 1;
    return increment;
}
