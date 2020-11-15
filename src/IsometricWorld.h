//
// Created by CedNaru on 09/10/2020.
//

#ifndef ISOMETRICMAPEDITOR_ISOMETRICWORLD_H
#define ISOMETRICMAPEDITOR_ISOMETRICWORLD_H


#include <containers/Grid3D.h>
#include <positionable/IsometricPositionable.h>
#include <Object.hpp>

namespace godot{

    class IsometricPositionable;

    class IsometricWorld {

    private:
        Array staticElements;
        Array dynamicElements;

        void renderIsometricElement(IsometricPositionable *positionable);

    public:
        IsometricWorld() = default;
        ~IsometricWorld() = default;

        void registerIsometricElement(IsometricPositionable* positionable);
        void unregisterIsometricElement(IsometricPositionable* positionable);

        void generateTopologicalRenderGraph();
    };

}


#endif //ISOMETRICMAPEDITOR_ISOMETRICWORLD_H
