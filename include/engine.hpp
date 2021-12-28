#include "particle.hpp"
#include <vector>
#include <math.h>

void collide(Particle& a, Particle& b){
    const float constant = dotProduct(a.velocity - b.velocity, a.position - b.position) / length(a.position - b.position)*length(a.position - b.position);
    a.speed(-2.0f*(a.position - b.position)*b.mass*constant / (b.mass + a.mass));
    b.speed(-2.0f*(b.position - a.position)*a.mass*constant / (a.mass + b.mass));
}

bool areColliding(const Particle& a, const Particle& b) {
    return distance(a.position, b.position) < a.mass + b.mass;
}

float length(sf::Vector2f v) {
    return sqrt(v.x*v.x + v.y*v.y);
}

float distance(sf::Vector2f a, sf::Vector2f b) {
    return length(a - b);
}

float dotProduct(sf::Vector2f a, sf::Vector2f b) {
    return a.x*b.x + a.y*b.y;
}

struct Engine {
    std::vector<Particle> particles;
    void update(float dt) {
        for (int i = 0; i < particles.size(); i++) {
            for (int j = i + 1; j < particles.size(); j++) {
                if (areColliding(particles[i], particles[j])) {
                    collide(particles[i], particles[j]);
                }
            }
        }
    }
};