#include <SFML/System/Vector2.hpp>
#include <vector>
#include "math.hpp"

struct Particle {
    sf::Vector2f position, velocity;
    float mass;
    int charge;
    Particle(sf::Vector2f p, float m, int c = 0, sf::Vector2f v = {0, 0}): position{p}, mass{m}, charge{c}, velocity{v} {}
    void speed(sf::Vector2f v) { velocity += v; }
    void update(float dt) {
        position += velocity*dt;
    }
};

struct Atom {
    std::vector<Particle*> particles;
    int tag = 0;
    Atom(Particle& p) {
        particles.push_back(&p);
    }
    Atom(sf::Vector2f p, float m, int e = 0, float a0 = 0) {
        particles.push_back(new Particle(p, m, 1));
        for (int i = 0; i < e; i++) {
            sf::Vector2f offset(31*cos(a0 + 2*i*M_PI / e), 31*sin(a0 + 2*i*M_PI / e));
            particles.push_back(new Particle(p + offset, 1.0f / 1840, -1, 1000.0f / 31 * sf::Vector2f(offset.y, -offset.x)));
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