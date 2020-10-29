//
// Created by CedNaru on 09/10/2020.
//

#include <positionable/StaticIsometricElement.h>
#include "IsometricWorld.h"

using namespace godot;

int IsometricWorld::registerIsometricElement(IsometricPositionable &positionable) {
    auto& staticElement = dynamic_cast<StaticIsometricElement&>(positionable);
    return 0;
}

bool IsometricWorld::unregisterIsometricElement(IsometricPositionable &positionable) {
    return 0;
}


void IsometricWorld::generateTopologicalRenderGraph() {
    currentSortingOrder = 0;
    const Array &positionables = world->getPositionables();
    for (int i = 0; i < positionables.size(); i++) {
        auto *positionable = cast_to<IsometricPositionable>(positionables[i]);
        if (positionable) {
            positionable->setRendered(false);
        }
    }
    for (int i = 0; i < positionables.size(); i++) {
        auto *positionable = cast_to<IsometricPositionable>(positionables[i]);
        if (positionable) {
            if (!positionable->isRendered()) {
                renderIsoNode(positionable);
            }
        }
    }

}

void IsometricWorld::renderIsoNode(IsometricPositionable *isoNode) {
    isoNode->setRendered(true);
    int maxZSize{0};
    const Array &isoNodes{getPositionableBehind(isoNode)};
    for (int i = 0; i < isoNodes.size(); i++) {
        auto *positionable = cast_to<IsometricPositionable>(isoNodes[i]);
        if (positionable) {
            if (!positionable->isRendered()) {
                renderIsoNode(positionable);
            }
            int positionableZOrderSize{positionable->getZOrderSize()};
            maxZSize = positionableZOrderSize >= maxZSize ? positionableZOrderSize : maxZSize;
        }
    }
    currentSortingOrder += maxZSize;
    isoNode->set_z_index(currentSortingOrder);
    currentSortingOrder += 1;
}

Array IsometricWorld::getPositionableBehind(IsometricPositionable *isoNode) {
    Array isoNodes;
    const Array &children{get_children()};
    for (int i = 0; i < children.size(); i++) {
        auto *positionable = cast_to<IsometricPositionable>(children[i]);
        if (positionable && positionable != isoNode) {
            if (IsometricServer::getInstance().doHexagoneOverlap(isoNode->getHexagoneCoordinates(),
                                                                 positionable->getHexagoneCoordinates())
                && IsometricServer::getInstance().isBoxInFront(isoNode->getAABB(), positionable->getAABB())) {
                isoNodes.append(positionable);
            }
        }
    }
    return isoNodes;
}
