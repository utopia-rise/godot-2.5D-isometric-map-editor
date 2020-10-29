//
// Created by CedNaru on 09/10/2020.
//

#ifndef ISOMETRICMAPEDITOR_ISOMETRICWORLD_H
#define ISOMETRICMAPEDITOR_ISOMETRICWORLD_H


#include <containers/Grid3D.h>
#include <positionable/IsometricPositionable.h>



namespace godot{

    class IsometricPositionable;

    class IsometricWorld {

    private:
        Array staticElements;
        Array dynamicElements;
        int currentSortingOrder;

        void renderIsoNode(IsometricPositionable *isoNode);
        Array getPositionableBehind(IsometricPositionable *isoNode);
    public:
        IsometricWorld() = default;
        ~IsometricWorld() = default;


        int registerIsometricElement(IsometricPositionable &positionable);
        bool unregisterIsometricElement(IsometricPositionable &positionable);

        void generateTopologicalRenderGraph();
    };

}


#endif //ISOMETRICMAPEDITOR_ISOMETRICWORLD_H
