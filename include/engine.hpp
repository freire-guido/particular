#include <SFML/Graphics.hpp>
#include <vector>
#include "particle.hpp"

void gravitate(Particle& a, Particle& b, float dt = 1, float cons = 1) {
    const sf::Vector2f direction = b.position - a.position;
    const float radiusSq = ((a.mass + b.mass)*(a.mass + b.mass));
    a.speed(dt*direction*cons*b.mass / radiusSq);
    b.speed(-dt*direction*cons*a.mass / radiusSq);
}

void gravitate(Particle& particle, sf::Vector2f point, float dt = 1, float cons = 1) {
    const sf::Vector2f direction = point - particle.position;
    const float radiusSq = 4*particle.mass*particle.mass; // Point mass equal to particle mass
    particle.speed(dt*direction*cons*particle.mass / radiusSq);
}

void collide(Particle& a, Particle& b) {
    const sf::Vector2f direction = b.position - a.position;
    const float constant = dotProduct(a.velocity - b.velocity, a.position - b.position) / ((b.mass + a.mass)*length(direction)*length(direction));
    a.speed(2.0f*direction*b.mass*constant);
    b.speed(-2.0f*direction*a.mass*constant);
}

bool areColliding(const Particle& a, const Particle& b) {
    return distance(a.position, b.position) < a.mass + b.mass;
}

struct Engine {
    std::vector<Atom> atoms;
    void add(Atom a) {
        atoms.push_back(a);
    }
    void add(std::vector<Atom> as){
        atoms.insert(atoms.end(), as.begin(), as.end());
    }
    void update(float dt) {
        for (int i = 0; i < atoms.size(); i++) {
            for (Particle* pA: atoms[i].particles) {
                for (int j = i + 1; j < atoms.size(); j++) {
                    for (Particle* pB: atoms[j].particles) {
                        if (areColliding(*pA, *pB)) {
                            collide(*pA, *pB);
                        }
                        gravitate(*pA, *pB, dt, 0.01);
                    }
                }
            }
            atoms[i].update(dt);
        }
    }
    void render(sf::RenderTarget& target) {
        std::vector<sf::CircleShape> objects(atoms.size());
        for (int i = 0; i < atoms.size(); i++){
            for (Particle* p: atoms[i].particles) {
                sf::CircleShape shape;
                sf::Color color(length(p->velocity)*100, 255, 0);
                shape.setPosition(p->position);
                shape.setFillColor(color);
                shape.setRadius(p->mass);
                shape.setOrigin(p->mass, p->mass);
                target.draw(shape);
            }
        }
    }
};