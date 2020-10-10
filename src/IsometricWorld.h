//
// Created by CedNaru on 09/10/2020.
//

#ifndef ISOMETRICMAPEDITOR_ISOMETRICWORLD_H
#define ISOMETRICMAPEDITOR_ISOMETRICWORLD_H


#include <containers/Grid3D.h>

namespace godot{

    class IsometricWorld {

    private:
        Array positionables;

    public:
        IsometricWorld() = default;
        ~IsometricWorld() = default;

        Array& getPositionables();
    };

}


#endif //ISOMETRICMAPEDITOR_ISOMETRICWORLD_H
