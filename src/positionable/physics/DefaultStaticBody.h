#ifndef ISOMETRICMAPEDITOR_DEFAULTSTATICBODY_H
#define ISOMETRICMAPEDITOR_DEFAULTSTATICBODY_H


#include <Godot.hpp>
#include <gen/StaticBody.hpp>
#include <positionable/IsometricPositionable.h>
#include <gen/CollisionShape.hpp>
#include <positionable/IsometricElement.h>
#include <DefaultBody.h>

namespace godot {

    /**
     * Default StaticBody for StaticIsometricElement with collision shapes calculated with dimensions of element.
     * @see godot::StaticIsometricElement
     */
    class DefaultStaticBody : public StaticBody, public DefaultBody<DefaultStaticBody, ConvexPolygonShape> {
        GODOT_CLASS(DefaultStaticBody, StaticBody)

    protected:
        void calculateCollisionShape() override;
        void updateCollisionShapes() override;

    public:
        static void _register_methods();

        DefaultStaticBody() = default;
        ~DefaultStaticBody() = default;

        void _init();
        void _enter_tree();
        void _physics_process(float delta);
    };
}


#endif //ISOMETRICMAPEDITOR_DEFAULTSTATICBODY_H
