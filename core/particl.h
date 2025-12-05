#ifndef PARTICL_PARTICL_H
#define PARTICL_PARTICL_H
#include <cstdint>

constexpr unsigned NUM_PARTICLES = 10000;
constexpr unsigned WIDTH = 700;
constexpr unsigned HEIGHT = 400;
// constexpr unsigned WIDTH = 64;
// constexpr unsigned HEIGHT = 64;


struct Particle {
    float x, y;
    float vx, vy;
    float elasticity;
    uint64_t age = 0;

    struct {
        uint8_t r, g, b, a;
    } color;
};


class Particl {
public:
    float gravity_direction = 90;
    float gravity_force = 100;

    Particl();

    void update(float dt);

    static Particle *getParticles();
};


#endif //PARTICL_PARTICL_H
