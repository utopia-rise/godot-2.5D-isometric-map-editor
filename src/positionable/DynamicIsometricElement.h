#ifndef ISOMETRICMAPEDITOR_DYNAMICISOMETRICELEMENT_H
#define ISOMETRICMAPEDITOR_DYNAMICISOMETRICELEMENT_H


#include <IsometricElement.h>
#include <DefaultKinematicBody.h>

namespace godot {

    class DynamicIsometricElement : public IsometricElement<DefaultKinematicBody> {
        GODOT_SUBCLASS(DynamicIsometricElement, IsometricElement)

    public:
        DynamicIsometricElement() = default;
        ~DynamicIsometricElement() = default;

        static void _register_methods();

        void _init();
        String get_class() const override;
    };

}


#endif //ISOMETRICMAPEDITOR_DYNAMICISOMETRICELEMENT_H
