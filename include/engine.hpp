#include <SFML/Graphics.hpp>
#include <vector>
#include "particle.hpp"
#include "math.hpp"

void gravitate(Particle&a, Particle& b, float cons = 1){
    const sf::Vector2f direction = b.position - a.position;
    a.accelerate(direction*cons*b.mass / ((a.mass + b.mass)*(a.mass + b.mass)));
    b.accelerate(-direction*cons*a.mass / ((a.mass + b.mass)*(a.mass + b.mass)));
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
            for (int j = i + 1; j < particles.size(); j++) {
                if (areColliding(particles[i], particles[j])) {
                    collide(particles[i], particles[j]);
                }
                gravitate(particles[i], particles[j]);
            }
            particles[i].update(dt);
        }
    }
    void render(sf::RenderTarget& target) {
        std::vector<sf::CircleShape> objects(particles.size());
        for (int i = 0; i < particles.size(); i++){
            sf::Color color(length(particles[i].velocity)*100, 255, 0);
            objects[i].setPosition(particles[i].position);
            objects[i].setFillColor(color);
            objects[i].setRadius(particles[i].mass);
            objects[i].setOrigin(particles[i].mass, particles[i].mass);
            target.draw(objects[i]);
        }

    }
};