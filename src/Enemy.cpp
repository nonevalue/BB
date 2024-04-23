#include "Enemy.hpp"

Enemy::Enemy()
{
    body.setRadius(20.f);
    body.setOrigin(20.f, 20.f);
    body.setOutlineThickness(2.f);
    body.setOutlineColor(sf::Color::Black);
    body.setPosition(200, 200);
    setColor(sf::Color::Red);
}

void Enemy::setColor(sf::Color color_value)
{
    body.setFillColor(color_value);
};

void Enemy::setHealth(int health_value)
{
    health_points-= health_value;
}

sf::Vector2f Enemy::getPosition()
{
    return body.getPosition();
}

void Enemy::update(sf::Vector2f player_position)
{
    updateVelocityVector(player_position);
    body.move(velocity_vector.x, velocity_vector.y);
};

void Enemy::randomizePosition(sf::Vector2f player_position)
{
    while (true)
    {
        float x = rand()%600;
        float y = rand()%600;
        float hypotenuse = sqrt(pow((player_position.x - x),2) + pow((player_position.y - y),2));
        if (hypotenuse > 100.f)
        {
            body.setPosition(x,y);
            break;
        }
    }
}

void Enemy::draw(sf::RenderTarget* window)
{
    window->draw(body);
};

void Enemy::updateVelocityVector(sf::Vector2f player_position)
{
    float x = player_position.x - body.getPosition().x;
    float y = player_position.y - body.getPosition().y;
    float hypotenuse = sqrt(pow(x, 2) + pow(y, 2));
    velocity_vector.x = velocity * (x / hypotenuse);
    velocity_vector.y = velocity * (y / hypotenuse);
}