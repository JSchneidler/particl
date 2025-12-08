#include "vector2.h"
#include <cmath>

float Vector2::dot(Vector2 b) {
    return x * b.x + y * b.y;
}

float Vector2::distance(Vector2 b) {
    return sqrt(pow((b.x - x), 2) + pow((b.y - y), 2));
}

float Vector2::magnitude() {
    return sqrt(pow(x, 2) + pow(y, 2));
}

Vector2 Vector2::normalize() {
    float mag = this->magnitude();
    return {x / mag, y / mag};
}

Vector2 Vector2::operator+(Vector2 b) {
    return {x + b.x, y + b.y};
}

Vector2 &Vector2::operator+=(const Vector2 &b) {
    x += b.x;
    y += b.y;
    return *this;
}

Vector2 Vector2::operator-(Vector2 b) {
    return {x - b.x, y - b.y};
}

Vector2 &Vector2::operator-=(const Vector2 &b) {
    x -= b.x;
    y -= b.y;
    return *this;
}

Vector2 Vector2::operator*(float a) {
    return {x * a, y * a};
}