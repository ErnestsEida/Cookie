#include <SFML/Graphics.hpp>

using namespace sf;

class GameShape {
private:
    Transformable* object_as_transformable;
    Drawable* object_as_drawable;
public:
    enum ShapeType{
        Circle,
        Rectangle,
    };

    GameShape(ShapeType);
    GameShape(ShapeType, float);
    GameShape(ShapeType, float, float);

    Transformable* GetAsTransformable() const;
};