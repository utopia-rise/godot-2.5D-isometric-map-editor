#ifndef ISOMETRICMAPEDITOR_DEFAULTSTATICBODY_H
#define ISOMETRICMAPEDITOR_DEFAULTSTATICBODY_H


#include <Godot.hpp>
#include <gen/StaticBody.hpp>
#include <positionable/IsometricPositionable.h>
#include <gen/CollisionShape.hpp>
#include <positionable/IsometricElement.h>

namespace godot {

    /**
     * Default StaticBody for StaticIsometricElement with collision shapes calculated with dimensions of element.
     * @see godot::StaticIsometricElement
     */
    class DefaultStaticBody : public StaticBody {
        GODOT_CLASS(DefaultStaticBody, StaticBody)

    private:
        CollisionShape *collisionShape;
        IsometricElement<DefaultStaticBody> *parent;

    public:
        static void _register_methods();

        DefaultStaticBody();
        ~DefaultStaticBody() = default;

        void _init();

        void _process(float delta);

        /**
         * Update collision shape according to slope type and dimensions.
         * @param slopeType
         * @param size
         */
        void updateCollisionShape();

        /**
         * Sets the parent node of this DefaultStaticBody. Should be a StaticIsometricElement.
         * @param staticIsometricElement
         */
        void setParent(IsometricElement<DefaultStaticBody> *staticIsometricElement);
    };
}


#endif //ISOMETRICMAPEDITOR_DEFAULTSTATICBODY_H
