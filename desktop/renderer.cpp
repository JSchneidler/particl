#include "renderer.h"
#include "particl.h"

static uint8_t pixels[WIDTH * HEIGHT * 4] = {0};

sf::Color toSfmlColor(Particle &p) {
    return sf::Color(p.color.r, p.color.g, p.color.b, p.color.a);
}

void updateSprite(sf::Texture &texture) {
    memset(pixels, 0, WIDTH * HEIGHT * 4);

    Particle *particles = Particl::getParticles();
    for (int i = 0; i < NUM_PARTICLES; i++) {
        Particle &p = particles[i];
        int x = static_cast<int>(round(p.x));
        int y = static_cast<int>(round(p.y));
        if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
            continue;

        int offset = (y * WIDTH + x) * 4;
        pixels[offset] = p.color.r;
        pixels[offset + 1] = p.color.g;
        pixels[offset + 2] = p.color.b;
        pixels[offset + 3] = p.color.a;
    }

    texture.update(pixels);
}

// void updateSprite(sf::Image &image, sf::Texture &texture) {
//
// }

