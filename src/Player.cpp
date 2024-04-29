#include "Player.hpp"

Player::Player()
{
    body.setRadius(20.f);
    body.setOrigin(20.f, 20.f);
    body.setPosition(300, 300);
    body.setFillColor(sf::Color::Green);
    body.setOutlineThickness(2.f);
    body.setOutlineColor(sf::Color::Black);

    gun.setSize(sf::Vector2f(30.f, 10.f));
    gun.setOrigin(30.f, 15.f);
    gun.setPosition(200, 200);
    gun.setFillColor(sf::Color(100, 100, 100));
    gun.setOutlineThickness(1.f);
    gun.setOutlineColor(sf::Color::Black);
}

void Player::update(sf::Vector2i mouse_position)
{
    gun.setPosition(body.getPosition());
    gun.setRotation(getangle(body.getPosition(), mouse_position));
}

void Player::move(sf::Vector2f move_speed)
{
    body.move(move_speed);
}

sf::Vector2f Player::getPosition()
{
    return body.getPosition();
}

void Player::setPosition(sf::Vector2f position_value)
{
    body.setPosition(position_value);
}

float Player::getRadius()
{
    return body.getRadius();
}

void Player::draw(sf::RenderTarget* window)
{
    window->draw(gun);
    window->draw(body);
}

float Player::getangle(sf::Vector2f player_position, sf::Vector2i mouse_position)
{
    float x = player_position.x - mouse_position.x;
    float y = player_position.y - mouse_position.y;
    return atan2(y, x) * 180 / 3.14;
}