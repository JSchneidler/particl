#include "particl.h"

#include <cstring>
#include <ctime>
#include <random>

Particle particles[NUM_PARTICLES]{0};
int16_t grid[WIDTH][HEIGHT];

constexpr float PARTICLE_LIFETIME_SECONDS = 5;
constexpr float PARTICLE_RADIUS = 0.75;
constexpr float MIN_DISTANCE = PARTICLE_RADIUS * 2;

inline float randomFloat() {
    return static_cast<float>(rand()) / RAND_MAX;
}

Particl::Particl() {
    srand(time(nullptr));

    for (int i = 0; i < NUM_PARTICLES; i++) {
        Particle &p = particles[i];
        p.pos = {randomFloat() * WIDTH, randomFloat() * HEIGHT};
        p.vel = {25 - randomFloat() * 50, 25 - randomFloat() * 50};
        p.elasticity = 1 - (randomFloat() * 0.10 + 0.85);
        p.drag = 1 - (randomFloat() * 0.05 + 0.05);
        uint8_t r = static_cast<uint8_t>(rand() % 255);
        uint8_t g = static_cast<uint8_t>(rand() % 255);
        uint8_t b = 255;
        p.color = {r, g, b, 255};
    }
}

void Particl::update(const float dt) {
    // Update spatial grid
    memset(grid, -1, sizeof(grid));
    for (int i = 0; i < NUM_PARTICLES; i++) {
        Particle &p = particles[i];
        auto x = static_cast<int>(round(p.pos.x));
        auto y = static_cast<int>(round(p.pos.y));
        p.next_in_cell = grid[x][y];
        grid[x][y] = i;
    }

    // Particle update
    for (Particle& p : particles) {
        p.age += dt;

        // Collision resolution
        auto px = static_cast<int>(round(p.pos.x));
        auto py = static_cast<int>(round(p.pos.y));
        for (int dx = -1; dx <= 1; dx++) {
            if (px + dx < 0 || px + dx >= WIDTH)
                continue;
            for (int dy = -1; dy <= 1; dy++) {
                if (py + dy < 0 || py + dy >= HEIGHT)
                    continue;

                auto head = grid[px + dx][py + dy];
                while (head != -1) {
                    Particle& p2 = particles[head];
                    if (&p != &p2) {
                        float distance = p.pos.distance(p2.pos);
                        if (distance < MIN_DISTANCE) {
                            Vector2 normal = (p2.pos - p.pos).normalize();
                            Vector2 relativeVel = p2.vel - p.vel;

                            Vector2 impulse = normal * relativeVel.dot(normal);
                            p.vel += impulse * p.elasticity;
                            p2.vel -= impulse * p2.elasticity;

                            Vector2 repulsion = normal * (MIN_DISTANCE - distance);
                            p.vel -= repulsion;
                            p2.vel += repulsion;
                        }
                    }
                    head = p2.next_in_cell;
                }
            }
        }

        // Gravity
        float force_mag = gravity_force * p.drag * dt;
        p.vel.x += cos(gravity_direction * (M_PI / 180)) * force_mag;
        p.vel.y += sin(gravity_direction * (M_PI / 180)) * force_mag;

        // Edges and update
        // TODO: Find good "speed" unit
        if (p.pos.x < 0) {
            p.pos.x = 0;
            p.vel.x *= -p.elasticity;
        } else if (p.pos.x >= WIDTH) {
            p.pos.x = WIDTH - PARTICLE_RADIUS;
            p.vel.x *= -p.elasticity;
        }

        if (p.pos.y < 0) {
            p.pos.y = 0;
            p.vel.y *= -p.elasticity;
        } else if (p.pos.y >= HEIGHT) {
            p.pos.y = HEIGHT - PARTICLE_RADIUS;
            p.vel.y *= -p.elasticity;
        }

        p.pos += p.vel * dt;

        // float ratio = (PARTICLE_LIFETIME_SECONDS * 1000) / (particles[i].age / 1000);
        // p.color.a = ratio * 255;
    }
}

Particle *Particl::getParticles() {
    return particles;
}
