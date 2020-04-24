#include "IsometricMap.h"
#include "../IsometricServer.h"

using namespace godot;

IsometricMap::IsometricMap() = default;

IsometricMap::~IsometricMap() = default;

void IsometricMap::_register_methods() {
    register_method("_init", &IsometricMap::_init);
    register_method("_process", &IsometricMap::_process);

    register_method("add_iso_positionable", &IsometricMap::addIsoPositionable);
    register_method("remove_iso_positionable", &IsometricMap::removeIsoPositionable);
    register_method("get_positionable_at", &IsometricMap::getPositionableAt);
    register_method("is_overlapping", &IsometricMap::isOverlapping);
    register_method("flatten", &IsometricMap::flatten);

    register_method("_on_resize", &IsometricMap::_onResize);
    register_method("_on_grid_updated", &IsometricMap::_onGridUpdated);
}

void IsometricMap::_init() {
    IsometricPositionable::_init();
}

void IsometricMap::_process(float delta) {
    generateTopologicalRenderGraph();
}

void IsometricMap::_onResize() {
    grid3D.updateArraySize(getSize3D());
    editionGrid3D.updateArraySize(getSize3D());
}

void IsometricMap::_onGridUpdated(int stair) {
    Array children = get_children();
    for (int i = 0; i < children.size(); i++) {
        IsometricPositionable *isometricPositionable = children[i];
        if (isometricPositionable) {
            isometricPositionable->_onGridUpdated(stair);
        }
    }
}

void IsometricMap::generateTopologicalRenderGraph() {
    currentSortingOrder = 0;
    const Array &children = get_children();
    for (int i = 0; i < children.size(); i++) {
        IsometricPositionable *positionable = children[i];
        if (positionable) {
            positionable->setRendered(false);
        }
    }
    for (int i = 0; i < children.size(); i++) {
        IsometricPositionable *positionable = children[i];
        if (positionable) {
            if (!positionable->isRendered()) {
                renderIsoNode(positionable);
            }
        }
    }
}

void IsometricMap::renderIsoNode(IsometricPositionable *isoNode) {
    isoNode->setRendered(true);
    int maxZSize = 0;
    Array isoNodes = getPositionableBehind(isoNode);
    for (int i = 0; i < isoNodes.size(); i++) {
        IsometricPositionable *positionable = isoNodes[i];
        if (positionable) {
            if (!positionable->isRendered()) {
                renderIsoNode(positionable);
            }
            int positionableZOrderSize = positionable->getZOrderSize();
            maxZSize = positionableZOrderSize >= maxZSize ? positionableZOrderSize : maxZSize;
        }
    }
    currentSortingOrder += maxZSize;
    isoNode->set_z_index(currentSortingOrder);
    currentSortingOrder += 1;
}

Array IsometricMap::getPositionableBehind(IsometricPositionable *isoNode) {
    Array isoNodes = Array();
    Array children = get_children();
    for (int i = 0; i < children.size(); i++) {
        IsometricPositionable *positionable = children[i];
        if (positionable && positionable != isoNode) {
            if (IsometricServer::doHexagoneOverlap(isoNode->getHexagoneCoordinates(), positionable->getHexagoneCoordinates())
            && IsometricServer::isBoxInFront(isoNode->getAABB(), positionable->getAABB())) {
                isoNodes.append(positionable);
            }
        }
    }
    return isoNodes;
}

Array IsometricMap::getFlattenPositionables(Vector3 offset) {
    Array positionables = Array();
    const Array &children = get_children();
    for (int i = 0; i < children.size(); i++) {
        IsometricPositionable *positionable = children[i];
        if (positionable) {
            if (auto *map = dynamic_cast<IsometricMap *>(positionable)) {
                const Array &innerPositionables = map->getFlattenPositionables(offset + map->getPosition3D());
                for (int j = 0; j < innerPositionables.size(); j++) {
                    IsometricPositionable *innerPositionable = innerPositionables[j];
                    if (innerPositionable) {
                        positionables.append(innerPositionable->duplicate());
                    }
                }
            } else {
                positionable->setPosition3D(offset + positionable->getPosition3D());
                positionables.append(positionable->duplicate());
            }
        }
    }
    return positionables;
}

IsometricMap *IsometricMap::copy() {
    IsometricMap *copy = IsometricMap::_new();
    copy->setAABB(getAABB());
    return copy;
}

void IsometricMap::addIsoPositionable(IsometricPositionable *isometricPositionable) {
    const Vector3 &mapSize = getAABB().size;
    const AABB &aabb = isometricPositionable->getAABB();
    const Vector3 pos = aabb.position;
    if (pos.x >= mapSize.x || pos.y >= mapSize.y || pos.z >= mapSize.z || editionGrid3D.isOverlapping(aabb)) return;
    isometricPositionable->setTemporary(false);
    isometricPositionable->setDebugZ(0);
    grid3D.setData(aabb.position, isometricPositionable);
    editionGrid3D.insertBox(aabb, isometricPositionable);
    add_child(isometricPositionable);
    isometricPositionable->add_to_group(ISO_GROUP, false);
}

void IsometricMap::removeIsoPositionable(IsometricPositionable *isometricPositionable) {
    const Vector3 &mapSize = getAABB().size;
    const AABB &aabb = isometricPositionable->getAABB();
    const Vector3 pos = aabb.position;
    if (pos.x >= mapSize.x || pos.y >= mapSize.y || pos.z >= mapSize.z) return;
    remove_child(isometricPositionable);
    grid3D.setData(aabb.position, nullptr);
    editionGrid3D.insertBox(aabb, isometricPositionable, true);
    if (isometricPositionable->is_in_group(ISO_GROUP)) {
        isometricPositionable->remove_from_group(ISO_GROUP);
    }
    isometricPositionable->update();
}

IsometricPositionable *IsometricMap::getPositionableAt(Vector3 pos, bool onlyLeftUpperCorner) {
    return (IsometricPositionable *)(onlyLeftUpperCorner ? grid3D.getData(pos) : editionGrid3D.getData(pos));
}

bool IsometricMap::isOverlapping(IsometricPositionable *positionable) {
    return editionGrid3D.isOverlapping(positionable->getAABB());
}

IsometricMap *IsometricMap::flatten() {
    auto *isometricMap = this->copy();
    const Array &flattenChildren = getFlattenPositionables();
    for (int i = 0; i < flattenChildren.size(); i++) {
        IsometricPositionable *it = flattenChildren[i];
        if (it) {
            isometricMap->addIsoPositionable(it);
        }
    }
    return isometricMap;
}
