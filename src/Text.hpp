#pragma once

#include <SFML/Graphics.hpp>

class Text
{
public:
    void createText(sf::Font* font, sf::Color font_color, int font_size, sf::Vector2f position_value, std::string string_value);
    void setColor(sf::Color color_value);
    void setText(std::string string_value);
    void setPosition(sf::Vector2f position_value);
    sf::FloatRect getRect();

    void draw(sf::RenderTarget* window);
private:
    sf::Text text_object;
};
