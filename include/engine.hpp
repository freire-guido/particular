#include <SFML/Graphics.hpp>
#include "particle.hpp"
#include <vector>
#include <math.h>

float dotProduct(sf::Vector2f a, sf::Vector2f b) {
    return a.x*b.x + a.y*b.y;
}

float length(sf::Vector2f v) {
    return sqrt(v.x*v.x + v.y*v.y);
}

float distance(sf::Vector2f a, sf::Vector2f b) {
    return length(a - b);
}

void collide(Particle& a, Particle& b){
    const float constant = dotProduct(a.velocity - b.velocity, a.position - b.position) / (length(a.position - b.position)*length(a.position - b.position));
    a.speed(-2.0f*(a.position - b.position)*b.mass*constant / (b.mass + a.mass));
    b.speed(-2.0f*(b.position - a.position)*a.mass*constant / (a.mass + b.mass));
}

bool areColliding(const Particle& a, const Particle& b) {
    return distance(a.position, b.position) < a.mass + b.mass;
}

struct Engine {
    std::vector<Particle> particles;
    void add(Particle p) {
        particles.push_back(p);
    }
    void add(std::vector<Particle> ps){
        particles.insert(particles.begin(), ps.begin(), ps.end());
    }
    void update(float dt) {
        for (int i = 0; i < particles.size(); i++) {
            particles[i].update(dt);
            for (int j = i + 1; j < particles.size(); j++) {
                if (areColliding(particles[i], particles[j])) {
                    collide(particles[i], particles[j]);
                }
            }
        }
    }
    void render(sf::RenderTarget& target) {
        std::vector<sf::CircleShape> objects(particles.size());
        for (int i = 0; i < particles.size(); i++){
            objects[i].setPosition(particles[i].position);
            objects[i].setFillColor(sf::Color::White);
            objects[i].setRadius(particles[i].mass);
            objects[i].setOrigin(particles[i].mass, particles[i].mass);
            target.draw(objects[i]);
        }

    }
};