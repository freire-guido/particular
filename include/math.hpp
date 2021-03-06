#include <SFML/Graphics.hpp>
#include <math.h>


float dotProduct(sf::Vector2f a, sf::Vector2f b) {
    return a.x*b.x + a.y*b.y;
}

float length(sf::Vector2f v) {
    return sqrt(v.x*v.x + v.y*v.y);
}

sf::Vector2f normalize(sf::Vector2f v) {
    return v / length(v);
}

float distance(sf::Vector2f a, sf::Vector2f b) {
    return length(a - b);
}