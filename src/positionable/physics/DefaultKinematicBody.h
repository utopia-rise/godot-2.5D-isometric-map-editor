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
        float speed;
        float gravity;

    protected:
        void updateCollisionShapes() override;

    public:
        static void _register_methods();

        DefaultKinematicBody();
        ~DefaultKinematicBody() = default;

        void _init();
        void _enter_tree();
        void _physics_process(float delta);

        float getSpeed() const;
        void setSpeed(float s);

        float getGravity() const;
        void setGravity(float g);
    };
}


#endif //ISOMETRICMAPEDITOR_DEFAULTKINEMATICBODY_H
