#pragma once

class Button
{
public:
    Button() {}
    Button(Texture &&texture){ _texture = std::move(texture); }

    void draw(){ _texture.draw(); }
    bool touch(float x, float y)
    {
        return _texture.position.x < x && (_texture.position.w + _texture.position.x) > x &&
            _texture.position.y < y && (_texture.position.h + _texture.position.y) > y ? 1 : 0;
    }

private:
    Texture _texture = {};
};