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
    class DefaultStaticBody : public StaticBody, public DefaultBody<DefaultStaticBody> {
        GODOT_CLASS(DefaultStaticBody, StaticBody)

    public:
        static void _register_methods();

        DefaultStaticBody() = default;
        ~DefaultStaticBody() = default;

        void _init();

        void _process(float delta);

        /**
         * Update collision shape according to slope type and dimensions.
         * @param slopeType
         * @param size
         */
        void updateCollisionShapes() override;

    };
}


#endif //ISOMETRICMAPEDITOR_DEFAULTSTATICBODY_H
