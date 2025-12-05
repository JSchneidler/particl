#include "particl.h"
#include <random>

Particle particles[NUM_PARTICLES]{0};

constexpr float PARTICLE_LIFETIME_SECONDS = 5;

inline double randomFloat() {
    return static_cast<double>(rand()) / RAND_MAX;
}

Particl::Particl() {
    srand(time(nullptr));

    for (int i = 0; i < NUM_PARTICLES; i++) {
        Particle &p = particles[i];
        p.x = rand() % WIDTH;
        p.y = rand() % HEIGHT;
        p.vx = 25 - randomFloat() * 50;
        p.vy = 25 - randomFloat() * 50;
        p.elasticity = (1 - (randomFloat() * 0.20 + 0.20));
        uint8_t r = static_cast<uint8_t>(rand() % 255);
        uint8_t g = static_cast<uint8_t>(rand() % 255);
        uint8_t b = static_cast<uint8_t>(rand() % 255);
        p.color = {r, g, b, 255};
    }
}

void Particl::update(const float dt) {
    for (int i = 0; i < NUM_PARTICLES; i++) {
        Particle &p = particles[i];
        p.age += dt;

        // TODO: Find good "speed" unit
        if (p.x < 0) {
            p.x = 0;
            p.vx *= -p.elasticity;
        } else if (p.x > WIDTH) {
            p.x = WIDTH - 1;
            p.vx *= -p.elasticity;
        } else {
            p.x += p.vx * dt;
        }

        if (p.y < 0) {
            p.y = 0;
            p.vy *= -p.elasticity;
        } else if (p.y > HEIGHT) {
            p.y = HEIGHT - 1;
            p.vy *= -p.elasticity;
        } else {
            p.y += p.vy * dt;
        }

        float force = gravity_force * dt;
        p.vx += cos(gravity_direction * (M_PI / 180)) * force * (1 - (randomFloat() * 0.05 + 0.05));
        p.vy += sin(gravity_direction * (M_PI / 180)) * force * (1 - (randomFloat() * 0.05 + 0.05));

        // float ratio = (PARTICLE_LIFETIME_SECONDS * 1000) / (particles[i].age / 1000);
        // p.color.a = ratio * 255;
    }
}

Particle *Particl::getParticles() {
    return particles;
}
