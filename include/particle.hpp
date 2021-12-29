#include <SFML/System/Vector2.hpp>

struct Particle {
    sf::Vector2f position, velocity;
    float mass; // Synonymous with radius in context
    Particle(sf::Vector2f p, float m): position{p}, mass{m} {}
    Particle(sf::Vector2f p, sf::Vector2f v, float m): position{p}, velocity{v}, mass{m} {}
    void speed(sf::Vector2f v) { velocity += v; }
    void update(float dt) {
        position += velocity*dt;
    }
};