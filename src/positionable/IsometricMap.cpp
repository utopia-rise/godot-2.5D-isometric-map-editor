#include "IsometricMap.h"
#include "../IsometricServer.h"

using namespace godot;

void IsometricMap::_init() {
    grid3D.updateArraySize(this->getAABB().size, true);
}

void IsometricMap::_process(float delta) {
    generateTopologicalRenderGraph();
}

void IsometricMap::setDrawTile(bool b) {
    drawTiles = b;
    update();
}

void IsometricMap::onResize(Vector3 size) {
    grid3D.updateArraySize(size);
    editionGrid3D.updateArraySize(size);
}

void IsometricMap::onGridUpdated(int stair) {
    Array children = get_children();
    for (int i = 0; i < children.size(); i++) {
        IsometricPositionable *isometricPositionable = children[i];
        if (isometricPositionable) {
            isometricPositionable->onGridUpdated(stair);
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
