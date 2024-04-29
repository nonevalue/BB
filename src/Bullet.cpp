#include "Bullet.hpp"

Bullet::Bullet()
{
    body.setRadius(6.f);
    body.setOrigin(6.f, 6.f);
    body.setFillColor(sf::Color(70, 70, 70));
    body.setOutlineThickness(1.f);
    body.setOutlineColor(sf::Color::Black);
    body.setPosition(300, 300);
}

void Bullet::resetBullet(sf::Vector2f player_position, sf::Vector2i cursor_position, int health_value)
{
    updateVelocityVector(player_position, cursor_position);
    body.setPosition(player_position.x + 2 * velocity_vector.x, player_position.y + 2 * velocity_vector.y);
    health_points = health_value;
}

int Bullet::getHealth()
{
    return health_points;
}


void Bullet::setHealth(int health_value)
{
    health_points = health_value;
}

sf::Vector2f Bullet::getPosition()
{
    return body.getPosition();
}

float Bullet::getRadius()
{
    return body.getRadius();
}


bool Bullet::isOutside()
{
    if (body.getPosition().x > 650 || body.getPosition().x < -50 ||
        body.getPosition().y > 650 || body.getPosition().y < -50)
        return true;
    else
        return false;
}

void Bullet::update()
{
    body.move(velocity_vector);
}

void Bullet::updateVelocityVector(sf::Vector2f player_position, sf::Vector2i cursor_position)
{
    float x = player_position.x - cursor_position.x;
    float y = player_position.y - cursor_position.y;
    float hypotenuse = sqrt(pow(x, 2) + pow(y, 2));
    velocity_vector.x = velocity * (x / hypotenuse) * -1;
    velocity_vector.y = velocity * (y / hypotenuse) * -1;
}

void Bullet::draw(sf::RenderTarget* window)
{
    window->draw(body);
}