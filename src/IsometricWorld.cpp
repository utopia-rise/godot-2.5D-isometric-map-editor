//
// Created by CedNaru on 09/10/2020.
//

#include <positionable/StaticIsometricElement.h>
#include <positionable/DynamicIsometricElement.h>
#include "IsometricWorld.h"
#include "IsometricServer.h"

using namespace godot;

IsometricWorld::IsometricWorld() {
    Godot::print("NEW ISOMETRIC WORLD");
}

IsometricWorld::~IsometricWorld() {
    Godot::print("BYE BYE ISOMETRIC WORLD");
}

void IsometricWorld::registerIsometricElement(IsometricPositionable* positionable) {

    if(auto staticElement = dynamic_cast<StaticIsometricElement*>(positionable)){
        for (int i = 0; i < staticElements.size(); i++) {
            auto* element =  Object::cast_to<IsometricPositionable>(staticElements[i]);
            if(element){
                if(IsometricServer::getInstance().doHexagoneOverlap(element->getHexagoneCoordinates(),
                                                                        staticElement->getHexagoneCoordinates())){
                    if(IsometricServer::getInstance().isBoxInFront(staticElement->getAABB(), element->getAABB())){
                        staticElement->behindStatics.append(element);
                    }
                    else{
                        element->behindStatics.append(staticElement);
                    }
                }
            }
        }
        staticElements.append(staticElement);
        Godot::print("static element added %s", staticElement->get_name());
    }
    else if(auto dynamicElement = dynamic_cast<DynamicIsometricElement*>(positionable)){
        dynamicElements.append(dynamicElement);
        Godot::print("dynamic element added %s", dynamicElement->get_name());
    }
}

void IsometricWorld::unregisterIsometricElement(IsometricPositionable* positionable) {
    if(auto staticElement = dynamic_cast<StaticIsometricElement*>(positionable)){
        staticElements.erase(staticElement);
        for (int i = 0; i < staticElements.size(); i++) {
            auto *element = Object::cast_to<IsometricPositionable>(staticElements[i]);
            element->behindStatics.erase(staticElement);

        }
        Godot::print("static element removed %s", staticElement->get_name());

    }
    else if(auto dynamicElement = dynamic_cast<DynamicIsometricElement*>(positionable)){
        dynamicElements.erase(dynamicElement);
        Godot::print("dynamic element removed %s", dynamicElement->get_name());
    }
    positionable->behindStatics.clear();
    positionable->behindDynamics.clear();
}


void IsometricWorld::generateTopologicalRenderGraph() {
    //Iterate the static and dynamic elements and clear them.
    for (int i = 0; i < staticElements.size(); ++i) {
        auto *positionable = Object::cast_to<IsometricPositionable>(staticElements[i]);
        if (positionable) {
            positionable->behindDynamics.clear();
            positionable->setRendered(false);
        }
    }
    for (int i = 0; i < dynamicElements.size(); ++i) {
        auto *positionable = Object::cast_to<IsometricPositionable>(dynamicElements[i]);
        if (positionable) {
            positionable->behindDynamics.clear();
            positionable->setRendered(false);
        }
    }

    for (int i = 0; i < dynamicElements.size(); ++i) {
        auto *dynamicPositionable = Object::cast_to<IsometricPositionable>(dynamicElements[i]);
        if (dynamicPositionable) {
            for (int j = 0; j < dynamicElements.size(); ++j){
                if(j != i){
                    auto *positionable = Object::cast_to<IsometricPositionable>(dynamicElements[j]);
                    if(positionable){
                        if(IsometricServer::getInstance().doHexagoneOverlap(dynamicPositionable->getHexagoneCoordinates(),
                                                                            positionable->getHexagoneCoordinates())){
                            if(IsometricServer::getInstance().isBoxInFront(dynamicPositionable->getAABB(), positionable->getAABB())){
                                dynamicPositionable->behindDynamics.append(positionable);
                            }
                            else{
                                positionable->behindDynamics.append(dynamicPositionable);
                            }
                        }
                    }
                }
            }
            for (int j = 0; j < staticElements.size(); ++j){
                auto *positionable = Object::cast_to<IsometricPositionable>(staticElements[j]);
                if(positionable){
                    if(IsometricServer::getInstance().doHexagoneOverlap(dynamicPositionable->getHexagoneCoordinates(),
                                                                        positionable->getHexagoneCoordinates())){
                        if(IsometricServer::getInstance().isBoxInFront(dynamicPositionable->getAABB(), positionable->getAABB())){
                            dynamicPositionable->behindDynamics.append(positionable);
                        }
                        else{
                            positionable->behindDynamics.append(dynamicPositionable);
                        }
                    }
                }
            }
        }
    }

    for (int i = 0; i < staticElements.size(); ++i) {
        auto *positionable = Object::cast_to<IsometricPositionable>(staticElements[i]);
        if (positionable && !positionable->isRendered()) {
            renderIsometricElement(positionable);
        }
    }
    for (int i = 0; i < dynamicElements.size(); ++i) {
        auto *positionable = Object::cast_to<IsometricPositionable>(dynamicElements[i]);
        if (positionable && !positionable->isRendered()) {
            renderIsometricElement(positionable);
        }
    }

}

void IsometricWorld::renderIsometricElement(IsometricPositionable *positionable) {
    positionable->setRendered(true);
    int maxZ = 0;
    for (int i = 0; i < positionable->behindStatics.size(); i++) {
        auto *behind = Object::cast_to<IsometricPositionable>(positionable->behindStatics[i]);
        if (behind) {
            if (!behind->isRendered()) {
                renderIsometricElement(behind);
            }
            int zOrderSize = positionable->getZOrderSize();
            int zOrder = behind->get_z_index();
            maxZ = zOrderSize >= maxZ ? zOrderSize + zOrder + 1 : maxZ;
        }
    }
    positionable->set_z_index(maxZ);
}
