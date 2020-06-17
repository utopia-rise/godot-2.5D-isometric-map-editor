#ifndef ISOMETRICMAPEDITOR_DEFAULTKINEMATICBODY_H
#define ISOMETRICMAPEDITOR_DEFAULTKINEMATICBODY_H


#include <Godot.hpp>
#include <KinematicBody.hpp>
#include <positionable/IsometricElement.h>
#include <DefaultBody.h>

namespace godot {

    class DefaultKinematicBody : public KinematicBody, public DefaultBody<DefaultKinematicBody> {
        GODOT_SUBCLASS(DefaultKinematicBody, KinematicBody);

    private:
        int speed;

    public:
        static void _register_methods();

        DefaultKinematicBody();
        ~DefaultKinematicBody() = default;

        void _init();
        void _process(float delta);

        void updateCollisionShapes() override;
    };
}


#endif //ISOMETRICMAPEDITOR_DEFAULTKINEMATICBODY_H
