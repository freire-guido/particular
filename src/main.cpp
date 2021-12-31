#include <SFML/Graphics.hpp>
#include "../include/engine.hpp"

int main() {
    int framerate = 60;
    float mass = 10;
    Engine engine;
    sf::RenderWindow window(sf::VideoMode(800, 600), "Particular");
    window.setFramerateLimit(framerate);
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::MouseButtonPressed) {
                engine.add(Atom(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window)), mass));
            }
            if (event.type == sf::Event::MouseWheelScrolled) {
                mass += event.mouseWheelScroll.delta;
                if (mass < 5) {
                    mass = 5;
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
