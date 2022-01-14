#include <SFML/Graphics.hpp>
#include "../include/engine.hpp"

int main() {
    int framerate = 60;
    float mass = 0.1;
    float x_center = 500;
    float y_center = 500;
    Engine engine;
    engine.add(Atom(*new Particle({x_center, y_center + 505}, 500, 0)));
    for (float i = x_center - 10; i <= x_center + 10; i += 1) {
        for (float j = y_center - 10; j <= y_center + 10; j += 1) {
            Atom fluid(*new Particle({i, j}, 0.1, 0));
            fluid.tag = 1;
            engine.add(fluid);
        }
    }
    sf::RenderWindow window(sf::VideoMode(800, 600), "Particular");
    window.setFramerateLimit(framerate);
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::MouseButtonPressed) {
                engine.add(Atom(*new Particle(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window)), mass, 0)));
            }
            if (event.type == sf::Event::MouseWheelScrolled) {
                mass++;
                if (mass < 1) {
                    mass = 1;
                }
            }
        }
        engine.update(1.0f/framerate);
        window.clear(sf::Color::Black);
        engine.render(window);
        window.display();
    }
    return 0;
}
