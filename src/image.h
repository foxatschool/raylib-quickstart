#pragma once

#include "shape.h"

class ImageShape : public Shape {
public:
    ImageShape() = default;

    ImageShape(const Texture2D texture, Vector2& position, float size = 20, const Color& color = WHITE) :
        Shape(position, size, color),
        texture_m{ texture }
    {}

    Type getType() override {return Type::IMAGE;} 
    void update() override;
    void draw() override;

    void SetTexture(const Texture2D& texture) { texture_m = texture; }


protected:
    Texture2D texture_m;
};