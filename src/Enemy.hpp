#pragma once

#include <SFML/Graphics.hpp>
#include <cmath>

class Enemy
{
public:
    Enemy();
    
    void setColor(sf::Color color_value);
    void setHealth(int health_value);
    sf::Vector2f getPosition();

    void update(sf::Vector2f player_position);
    void randomizePosition(sf::Vector2f player_position);
    
    void draw(sf::RenderTarget* window);
private:
    void updateVelocityVector(sf::Vector2f player_position);
    sf::CircleShape body;
    sf::Vector2f velocity_vector;
    float velocity = 2.f;

    int health_points = 1;
};
