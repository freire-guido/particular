#include <SFML/Graphics.hpp>
#include "../include/engine.hpp"

int main() {
    Engine engine;
    engine.add({Particle({0, 0}, {1, 1}, 5), Particle({50, 50}, {-1, -1}, 3)});

    int framerate = 60;
    sf::RenderWindow window(sf::VideoMode(800, 600), "Particular");
    window.setFramerateLimit(framerate);
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
        engine.update(1.0f/framerate);
        window.clear(sf::Color::Black);
        engine.render(window);
        window.display();
    }
    return 0;
}
