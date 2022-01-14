#include <SFML/Graphics.hpp>
#include <vector>
#include "particle.hpp"

float gravitate(Particle& a, Particle& b, float dt = 1, float cons = 1) {
    const sf::Vector2f direction = normalize(b.position - a.position);
    const float radiusSq = length(b.position - a.position)*length(b.position - a.position);
    const float force = cons*a.mass*b.mass / radiusSq;
    a.speed(dt*direction*force / a.mass);
    b.speed(-dt*direction*force / b.mass);
    return force;
}

float magnetize(Particle& a, Particle& b, float dt = 1, float cons = 1) {
    const sf::Vector2f direction = normalize(b.position - a.position);
    const float radiusSq = length(b.position - a.position)*length(b.position - a.position);
    const float force = cons*static_cast<float>(a.charge)*static_cast<float>(b.charge) / radiusSq;
    a.speed(-dt*direction*force);
    b.speed(dt*direction*force);
    return force;
}

void collide(Particle& a, Particle& b) {
    const sf::Vector2f direction = b.position - a.position;
    const float distanceSq = length(direction)*length(direction);
    const float constant = dotProduct(a.velocity - b.velocity, a.position - b.position) / ((b.mass + a.mass)*distanceSq);
    a.speed(2.0f*direction*b.mass*constant);
    b.speed(-2.0f*direction*a.mass*constant);
}

bool areColliding(const Particle& a, const Particle& b) {
    return distance(a.position, b.position) <= a.mass + b.mass;
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
            for (int j = 0; j < atoms[i].particles.size(); j++) {
                for (int t = j + 1; t < atoms[i].particles.size(); t++) {
                    if (areColliding(*atoms[i].particles[j], *atoms[i].particles[t])) {
                        collide(*atoms[i].particles[j], *atoms[i].particles[t]);
                    }
                    gravitate(*atoms[i].particles[j], *atoms[i].particles[t], dt, 10);
                    magnetize(*atoms[i].particles[j], *atoms[i].particles[t], dt, 10);
                }
                for (int s = i + 1; s < atoms.size(); s++) {
                    float interaction = atoms[s].tag == atoms[i].tag ? 100 : 10;
                    for (int t = 0; t < atoms[s].particles.size(); t++) {
                        if (areColliding(*atoms[i].particles[j], *atoms[s].particles[t])) {
                            collide(*atoms[i].particles[j], *atoms[s].particles[t]);
                        }
                        gravitate(*atoms[i].particles[j], *atoms[s].particles[t], dt, interaction);
                        magnetize(*atoms[i].particles[j], *atoms[s].particles[t], dt, 10);
                    }
                }
            }
        }
        for (int i = 0; i < atoms.size(); i++) {
            for (int j = 0; j < atoms[i].particles.size(); j++) {
                atoms[i].particles[j]->update(dt);
            }
        }
    }
    void render(sf::RenderTarget& target) {
        for (int i = 0; i < atoms.size(); i++){
            for (Particle* p: atoms[i].particles) {
                sf::CircleShape shape;
                sf::Color color(p->charge > 0 ? 255 : 0, p->charge == 0 ? 255 : 0, p->charge > 0 ? 0 : 255);
                shape.setPosition(p->position);
                shape.setFillColor(color);
                shape.setRadius(1 + p->mass);
                shape.setOrigin(p->mass, p->mass);
                target.draw(shape);
            }
        }
    }
};