#ifndef PARTICL_PARTICL_H
#define PARTICL_PARTICL_H
#include "vector2.h"
#include <cstdint>

constexpr unsigned NUM_PARTICLES = 1000;
// constexpr unsigned WIDTH = 700;
// constexpr unsigned HEIGHT = 400;
constexpr unsigned WIDTH = 64;
constexpr unsigned HEIGHT = 64;

struct Particle {
    Vector2 pos {0, 0};
    Vector2 pos_old {0, 0};
    float elasticity;
    float drag;
    float age = 0;

    struct {
        uint8_t r, g, b, a;
    } color;

    int16_t next_in_cell = -1;
};


class Particl {
public:
    float gravity_direction = 90;
    float gravity_force = 1000;

    Particl();

    void update(float dt);

    static Particle *getParticles();
};


#endif //PARTICL_PARTICL_H
