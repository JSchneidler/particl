#include "particl.h"

#include <cstring>
#include <ctime>
#include <random>

Particle particles[NUM_PARTICLES]{0};
int16_t grid[WIDTH][HEIGHT];

constexpr int NUM_COLLISION_ITERATIONS = 3;
constexpr float PARTICLE_LIFETIME_SECONDS = 5;
constexpr float PARTICLE_RADIUS = 0.5;
constexpr float MIN_DISTANCE = PARTICLE_RADIUS * 2;

inline float randomFloat() {
    return static_cast<float>(rand()) / RAND_MAX;
}

Particl::Particl() {
    srand(time(nullptr));

    for (int i = 0; i < NUM_PARTICLES; i++) {
        Particle &p = particles[i];
        p.pos = {randomFloat() * WIDTH, randomFloat() * HEIGHT};
        // p.vel = {25 - randomFloat() * 50, 25 - randomFloat() * 50};
        p.elasticity = 0.1 + randomFloat() * 0.2;
        p.drag = 0.995 + randomFloat() * 0.004;
        uint8_t r = static_cast<uint8_t>(rand() % 255);
        uint8_t g = static_cast<uint8_t>(rand() % 255);
        uint8_t b = 255;
        p.color = {r, g, b, 255};
    }
}

void Particl::update(const float dt) {
    float ax = cos(gravity_direction * (M_PI / 180)) * gravity_force;
    float ay = sin(gravity_direction * (M_PI / 180)) * gravity_force;
    Vector2 a = Vector2{ax, ay};
    for (Particle& p : particles) {
        p.age += dt;

        Vector2 vel = (p.pos - p.pos_old) * p.drag;
        Vector2 new_old = p.pos;
        p.pos += vel + (a * dt * dt);
        p.pos_old = new_old;
    }

    // Collision resolution
    for (int it = 0; it < NUM_COLLISION_ITERATIONS; it++) {
        // Update spatial grid
        memset(grid, -1, sizeof(grid));
        for (int i = 0; i < NUM_PARTICLES; i++) {
            Particle &p = particles[i];
            int x = static_cast<int>(floor(p.pos.x));
            int y = static_cast<int>(floor(p.pos.y));
            x = (x < 0) ? 0 : (x >= WIDTH ? WIDTH - 1 : x);
            y = (y < 0) ? 0 : (y >= HEIGHT ? HEIGHT - 1 : y);

            p.next_in_cell = grid[x][y];
            grid[x][y] = i;
        }

        for (int i = 0; i < NUM_PARTICLES; i++) {
            Particle &p = particles[i];

            auto px = static_cast<int>(floor(p.pos.x));
            auto py = static_cast<int>(floor(p.pos.y));
            px = (px < 0) ? 0 : (px >= WIDTH ? WIDTH - 1 : px);
            py = (py < 0) ? 0 : (py >= HEIGHT ? HEIGHT - 1 : py);
            for (int dx = -1; dx <= 1; dx++) {
                if (px + dx < 0 || px + dx >= WIDTH)
                    continue;
                for (int dy = -1; dy <= 1; dy++) {
                    if (py + dy < 0 || py + dy >= HEIGHT)
                        continue;

                    auto head = grid[px + dx][py + dy];
                    while (head != -1) {
                        Particle& p2 = particles[head];
                        if (&p != &p2 && i < head) {
                            float distance = p.pos.distance(p2.pos);
                            if (distance < MIN_DISTANCE) {
                                Vector2 normal = (p2.pos - p.pos).normalize();
                                float overlap = MIN_DISTANCE - distance;
                                p.pos -= normal * (overlap / 2);
                                p2.pos += normal * (overlap / 2);
                            }
                        }
                        head = p2.next_in_cell;
                    }
                }
            }

            // float ratio = (PARTICLE_LIFETIME_SECONDS * 1000) / (particles[i].age / 1000);
            // p.color.a = ratio * 255;
        }

        for (Particle &p : particles) {
            if (p.pos.x < 0) {
                float vx = p.pos.x - p.pos_old.x;
                p.pos.x = 0;
                if (vx < 0) p.pos_old.x = p.pos.x + (vx * p.elasticity);
            } else if (p.pos.x > WIDTH - PARTICLE_RADIUS) {
                float vx = p.pos.x - p.pos_old.x;
                p.pos.x = WIDTH - PARTICLE_RADIUS;
                if (vx > 0) p.pos_old.x = p.pos.x + (vx * p.elasticity);
            }

            if (p.pos.y < 0) {
                float vy = p.pos.y - p.pos_old.y;
                p.pos.y = 0;
                if (vy < 0) p.pos_old.y = p.pos.y + (vy * p.elasticity);
            } else if (p.pos.y > HEIGHT - PARTICLE_RADIUS) {
                float vy = p.pos.y - p.pos_old.y;
                p.pos.y = HEIGHT - PARTICLE_RADIUS;
                if (vy > 0) p.pos_old.y = p.pos.y + (vy * p.elasticity);
            }
        }
    }
}

Particle *Particl::getParticles() {
    return particles;
}
