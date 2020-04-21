#include "IsometricMap.h"
#include "../IsometricServer.h"

using namespace godot;

void IsometricMap::_register_methods() {
    register_method("_init", &IsometricMap::_init);
    register_method("_process", &IsometricMap::_process);

    register_method("add_iso_positionable", &IsometricMap::addIsoPositionable);
    register_method("remove_iso_positionable", &IsometricMap::removeIsoPositionable);
    register_method("get_positionable_at", &IsometricMap::getPositionableAt);
    register_method("is_overlapping", &IsometricMap::isOverlapping);

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
    int maxZSize;
    Array isoNodes = getPositionableBehind(isoNode);
    for (int i = 0; i < isoNodes.size(); i++) {
        IsometricPositionable *positionable = isoNodes[i];
        if (positionable) {
            if (positionable->isRendered()) {
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

void IsometricMap::addIsoPositionable(IsometricPositionable *isometricPositionable) {
    isometricPositionable->setTemporary(false);
    isometricPositionable->setDebugZ(0);
    const AABB &aabb = isometricPositionable->getAABB();
    grid3D.setData(aabb.position, isometricPositionable);
    editionGrid3D.insertBox(aabb, isometricPositionable);
    add_child(isometricPositionable);
    isometricPositionable->add_to_group(ISO_GROUP, false);
}

void IsometricMap::removeIsoPositionable(IsometricPositionable *isometricPositionable) {
    remove_child(isometricPositionable);
    const AABB &aabb = isometricPositionable->getAABB();
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
