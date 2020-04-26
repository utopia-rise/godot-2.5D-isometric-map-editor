#ifndef ISOMETRICMAPEDITOR_PLACEHOLDERTYPE_H
#define ISOMETRICMAPEDITOR_PLACEHOLDERTYPE_H

#include <gen/Resource.hpp>
#include <Godot.hpp>

namespace godot {

    class PlaceholderType : public Resource {
        GODOT_CLASS(PlaceholderType, Resource)

    private:
        String typeName;
        Color color;

    public:
        static void _register_methods();

        void _init();

        String getTypeName() const;
        void setTypeName(String name);
        Color getColor() const;
        void setColor(Color col);
    };

}

#endif //ISOMETRICMAPEDITOR_PLACEHOLDERTYPE_H
