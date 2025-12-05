#include "particl.h"
#include "renderer.h"
#include <SFML/Graphics.hpp>

constexpr unsigned SCALE = 2;
// constexpr unsigned SCALE = 10;


int main() {
    sf::RenderWindow window(sf::VideoMode({WIDTH * SCALE, HEIGHT * SCALE}), "Particl");
    Particl particl;
    sf::Clock clock;

    sf::Texture texture(sf::Vector2u{WIDTH, HEIGHT});
    sf::Sprite sprite(texture);

    sf::Font font("Basic-Regular.ttf");
    sf::Text text(font);

    text.setCharacterSize(24);
    text.setPosition({10, 10});
    text.setFillColor(sf::Color::White);
    float fps = 0;

    sf::RectangleShape line({50.f, 5.f});
    line.setFillColor(sf::Color::Red);
    line.setPosition({50, 150});

    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>())
                window.close();
            else if (const auto *keyPressed = event->getIf<sf::Event::KeyPressed>()) {
                if (keyPressed->scancode == sf::Keyboard::Scan::Left)
                    particl.gravity_direction -= 15;
                else if (keyPressed->scancode == sf::Keyboard::Scan::Right)
                    particl.gravity_direction += 15;
                else if (keyPressed->scancode == sf::Keyboard::Scan::Up)
                    particl.gravity_force += 10;
                    // particl.gravity_direction = 270;
                else if (keyPressed->scancode == sf::Keyboard::Scan::Down)
                    particl.gravity_force -= 10;
                    // particl.gravity_direction = 90;
            }
        }

        sf::Time dt = clock.restart();
        fps = 1.0 / dt.asSeconds();
        text.setString(std::format("{}\n{}@{}", round(fps),  particl.gravity_direction, particl.gravity_force));
        line.setRotation(sf::degrees(particl.gravity_direction));
        particl.update(dt.asSeconds());
        updateSprite(texture);
        sprite.setScale({SCALE, SCALE});

        window.clear();
        window.draw(sprite);
        window.draw(text);
        window.draw(line);
        window.display();
    }

    return 0;
}
