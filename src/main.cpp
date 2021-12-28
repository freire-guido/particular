#include <SFML/Graphics.hpp>

int main() {
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
        window.clear(sf::Color::Black);
        window.display();
    }
    return 0;
}
