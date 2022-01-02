#include <SFML/Graphics.hpp>
#include <vector>
#include "particle.hpp"

void gravitate(Particle& a, Particle& b, float dt = 1, float cons = 1) {
    const sf::Vector2f direction = normalize(b.position - a.position);
    const float radiusSq = length(direction)*length(direction);
    a.speed(dt*direction*cons*static_cast<float>(b.charge)*b.mass / radiusSq);
    b.speed(-dt*direction*cons*static_cast<float>(a.charge)*a.mass / radiusSq);
}

void collide(Particle& a, Particle& b) {
    const sf::Vector2f direction = normalize(b.position - a.position);
    const float constant = dotProduct(a.velocity - b.velocity, a.position - b.position) / ((b.mass + a.mass)*length(direction)*length(direction));
    a.speed(2.0f*direction*b.mass*constant);
    b.speed(-2.0f*direction*a.mass*constant);
}

bool areColliding(const Particle& a, const Particle& b) {
    return distance(a.position, b.position) < a.mass + b.mass;
}

struct Engine {
    std::vector<Atom> atoms;
    bool collisions = false; // Toggle elastic collisions
    void add(Atom a) {
        atoms.push_back(a);
    }
    void add(std::vector<Atom> as){
        atoms.insert(atoms.end(), as.begin(), as.end());
    }
    void update(float dt) {
        for (int i = 0; i < atoms.size(); i++) {
            for (int j = 0; j < atoms[i].particles.size(); j++) {
                for (int s = i; s < atoms.size(); s++) {
                    for (int t = 0; t < atoms[s].particles.size(); t++) {
                        if (i != s || j != t) {
                            if (collisions && areColliding(*atoms[i].particles[j], *atoms[s].particles[t])) {
                                collide(*atoms[i].particles[j], *atoms[s].particles[t]);
                            }
                            gravitate(*atoms[i].particles[j], *atoms[s].particles[t], dt, 31);
                        }
                    }
                }
                atoms[i].particles[j]->update(dt);
            }
        }
    }
    void render(sf::RenderTarget& target) {
        for (int i = 0; i < atoms.size(); i++){
            for (Particle* p: atoms[i].particles) {
                sf::CircleShape shape;
                sf::Color color(p->charge > 0 ? 255 : 0, 0, p->charge > 0 ? 0 : 255);
                shape.setPosition(p->position);
                shape.setFillColor(color);
                shape.setRadius(1 + p->mass);
                shape.setOrigin(p->mass, p->mass);
                target.draw(shape);
            }
        }
    }
};