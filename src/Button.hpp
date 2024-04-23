#pragma once

#include "Text.hpp"

#include <iostream>

class Button
{
public:
    Button(sf::Vector2f button_size, sf::Vector2f button_position, sf::Color button_color, sf::Font* font, sf::Color font_color, int font_size, std::string string_value);
    Button(sf::Vector2f button_size, sf::Vector2f button_position, sf::Color button_color, float outline_thickness_value, sf::Color outline_color_value, sf::Color hover_color_value, sf::Color click_color_value, bool* return_pointer_value, sf::Font* font, sf::Color font_color, int font_size, std::string string_value);
    void setSize(sf::Vector2f button_size);
    void setPosition(sf::Vector2f button_position);
    void setText(std::string string_value);
    void setColor(sf::Color outline_color, sf::Color hover_color, sf::Color click_color);
    void setReturnPointer(bool* return_pointer_value);

    void update(sf::Vector2i cursor_position, bool left_mouse_click);

    void draw(sf::RenderTarget* window);
private:
    sf::Vector2f textPosition(sf::Vector2f button_size, sf::Vector2f button_position);
    sf::RectangleShape button_body;
    Text text;
    bool pressed = false;
    sf::Color outline_color = sf::Color::Black;
    sf::Color hover_color = sf::Color::Red;
    sf::Color click_color = sf::Color::Green;

    bool* return_pointer = nullptr;
};