#include "Text.hpp"

void Text::createText(sf::Font* font, sf::Color font_color, int font_size, sf::Vector2f position_value, std::string string_value)
{
    text_object.setFont(*font);
    text_object.setCharacterSize(font_size);
    text_object.setFillColor(font_color);
    text_object.setPosition(position_value);
    text_object.setString(string_value);
}

void Text::setColor(sf::Color color_value)
{
    text_object.setFillColor(color_value);
}

void Text::setText(std::string string_value)
{
    text_object.setString(string_value);
}

void Text::setPosition(sf::Vector2f position_value)
{
    text_object.setPosition(position_value);
}

sf::FloatRect Text::getRect()
{
    return text_object.getGlobalBounds();
}

void Text::draw(sf::RenderTarget* window)
{
    window->draw(text_object);
}