#ifndef PARTICL_VECTOR2_H
#define PARTICL_VECTOR2_H

struct Vector2 {
    float x, y;

    float dot(Vector2 b);
    float distance(Vector2 b);
    float magnitude();
    Vector2 normalize();

    Vector2 operator+(Vector2 b);
    Vector2 operator-(Vector2 b);
    Vector2 operator*(float a);
    Vector2 &operator+=(const Vector2 &b);
    Vector2 &operator-=(const Vector2 &b);
};

#endif //PARTICL_VECTOR2_H