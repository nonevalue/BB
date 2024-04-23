#pragma once

#include <SFML/Graphics.hpp>
#include <cmath>

class Bullet
{
public:
    Bullet();
    void resetBullet(sf::Vector2f player_position, sf::Vector2i cursor_position, int health_value);
    bool isOutside();
    void update();
    
    void draw(sf::RenderTarget* window);
private:
    void updateVelocityVector(sf::Vector2f player_position, sf::Vector2i cursor_position);
    sf::CircleShape body;
    sf::Vector2f velocity_vector;
    float velocity = 15.f;
    int health_points;
};
