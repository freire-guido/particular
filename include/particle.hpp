#include <SFML/System/Vector2.hpp>
#include <vector>
#include "math.hpp"

struct Particle {
    sf::Vector2f position, velocity;
    int charge;
    Particle(sf::Vector2f p, int c): position{p}, charge{c} {}
    Particle(sf::Vector2f p, sf::Vector2f v, int c): position{p}, velocity{v}, charge{c} {}
    float mass() const { return abs(charge); }
    void speed(sf::Vector2f v) { velocity += v; }
    void update(float dt) {
        position += velocity*dt;
    }
};

struct Atom {
    std::vector<Particle*> particles;
    Atom(sf::Vector2f p, int m) {
        particles.push_back(new Particle(p, m));
        for (int i = 0; i < m; i++) {
            sf::Vector2f offset(2*m*cos(2*i*M_PI / m), 2*m*sin(2*i*M_PI / m));
            particles.push_back(new Particle(p + offset, sf::Vector2f(offset.y, -offset.x), -1));
        }
    }
    Atom(sf::Vector2f p, int m, int e) {
        particles.push_back(new Particle(p, m));
        for (int i = 0; i < e; i++) {
            sf::Vector2f offset(2*m*cos(2*i*M_PI / e), 2*m*sin(2*i*M_PI / e));
            particles.push_back(new Particle(p + offset, sf::Vector2f(offset.y, -offset.x), -1));
        }
    }
    void speed(sf::Vector2f v) {
        particles[0]->speed(v);
    }
    void update(float dt){
        for (Particle* p: particles) {
            p->position = p->velocity*dt;
        }
    }
};