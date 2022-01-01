#include <SFML/System/Vector2.hpp>
#include <vector>
#include "math.hpp"

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

struct Atom {
    std::vector<Particle> electrons;
    Particle nucleus;
    std::vector<Particle*> particles;
    Atom(sf::Vector2f p, float m): nucleus{p, m} {
        particles.push_back(&nucleus);
        for (int i = 0; i < m; i++) {
            sf::Vector2f offset(2*m*cos(2*i*M_PI / m), 2*m*sin(2*i*M_PI / m));
            electrons.push_back(Particle(p + offset, sf::Vector2f(offset.y, -offset.x) / length(offset), 1));
            particles.push_back(&electrons[i]);
        }
    }
    void speed(sf::Vector2f v) { nucleus.speed(v); }
    void update(float dt){
        nucleus.position += nucleus.velocity*dt;
        for (Particle& electron: electrons) {
            electron.position += nucleus.velocity*dt;
        }
    }
};