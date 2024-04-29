#pragma once

#include <SFML/Graphics.hpp>

#include <iostream>
#include <cmath>

#include "Enemy.hpp"

class Bullet
{
public:
    Bullet();
    void resetBullet(sf::Vector2f player_position, sf::Vector2i cursor_position, int health_value);
    int getHealth();
    void setHealth(int health_value);
    sf::Vector2f getPosition();
    float getRadius();
    
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
