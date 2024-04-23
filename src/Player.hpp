#pragma once

#include <SFML/Graphics.hpp>
#include <cmath>

class Player
{
public:
    Player();
    void update(sf::Vector2i mouse_position);
    void move(sf::Vector2f move_speed);
    sf::Vector2f getPosition();
    
    void draw(sf::RenderTarget* window);
private:
    float getangle(sf::Vector2f player_position, sf::Vector2i mouse_position);
    sf::CircleShape body;
    sf::RectangleShape gun;
};
