#ifndef ISOMETRICMAPEDITOR_DEFAULTSTATICBODY_H
#define ISOMETRICMAPEDITOR_DEFAULTSTATICBODY_H


#include <Godot.hpp>
#include <gen/StaticBody.hpp>
#include <positionable/IsometricPositionable.h>
#include <gen/CollisionShape.hpp>

namespace godot {
    /**
     * Default StaticBody for StaticIsometricElement with collision shapes calculated with dimensions of element.
     * @see godot::StaticIsometricElement
     */
    class DefaultStaticBody : public StaticBody {
        GODOT_CLASS(DefaultStaticBody, StaticBody)

    private:
        CollisionShape *collisionShape;

        /**
         * Add base (lower) points of slope shapes.
         * @param poolVector3Array
         */
        static void addBasePointsForSlope(PoolVector3Array &poolVector3Array, const Vector3 &size, const Vector3 &originPoint);
    public:
        static void _register_methods();

        DefaultStaticBody();
        ~DefaultStaticBody() = default;

        void _init();

        /**
         * Update collision shape according to slope type and dimensions.
         * @param slopeType
         * @param size
         */
        void updateCollisionShape(SlopeType slopeType, const Vector3 &size);
    };
}


#endif //ISOMETRICMAPEDITOR_DEFAULTSTATICBODY_H
