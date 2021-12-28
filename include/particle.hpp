#include <SFML/System/Vector2.hpp>

struct Particle {
    sf::Vector2f position, velocity, acceleration;
    float mass; // Synonymous with radius in context
    void accelerate(sf::Vector2f a) { acceleration += a; }
    void speed(sf::Vector2f v) { velocity += v; }
    void update(float dt) {
        velocity += acceleration*dt;
        position += velocity*dt;
    }
};