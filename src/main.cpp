#include <SFML/Graphics.hpp>
#include "../include/engine.hpp"

int main() {
    int framerate = 200;
    int mass = 1;
    float dist = 200;
    Engine engine(true);
    sf::RenderWindow window(sf::VideoMode(800, 600), "Particular");
    //engine.add(Atom(*new Particle({1000, 500}, 1000)));
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
