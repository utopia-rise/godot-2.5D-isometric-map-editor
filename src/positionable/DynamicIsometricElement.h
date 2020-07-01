#ifndef ISOMETRICMAPEDITOR_DYNAMICISOMETRICELEMENT_H
#define ISOMETRICMAPEDITOR_DYNAMICISOMETRICELEMENT_H


#include <IsometricElement.h>
#include <DefaultKinematicBody.h>

namespace godot {

    class DynamicIsometricElement : public IsometricElement<DefaultKinematicBody> {
        GODOT_SUBCLASS(DynamicIsometricElement, IsometricPositionable)

    public:
        DynamicIsometricElement() = default;
        ~DynamicIsometricElement() = default;

        static void _register_methods();

        void _init();
        void _enter_tree();
        String get_class() const override;

        bool getHasDefaultBody() const override;
        void setHasDefaultBody(bool b) override;

        bool getHasMoved() const override;
        void setHasMoved(bool hm) override;

        void updatePositionFromBody(PhysicsBody *physicsBody) override;
    };

}


#endif //ISOMETRICMAPEDITOR_DYNAMICISOMETRICELEMENT_H
