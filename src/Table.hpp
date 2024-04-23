#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>

#include "Text.hpp"
#include "Button.hpp"

class Table
{
public:
    Table();
    Table(sf::Vector2f position, sf::Vector2f size, sf::Color table_color);
    void create(sf::Vector2f position, sf::Vector2f size, sf::Color table_color);
    void addText(sf::Font* font, sf::Color font_color, int font_size, sf::Vector2f position_value, std::string string_value);
    void addButton(sf::Vector2f button_size, sf::Vector2f button_position, sf::Color button_color, float outline_thickness_value, sf::Color outline_color_value, sf::Color hover_color_value, sf::Color click_color_value, bool* return_pointer_value, sf::Font* font, sf::Color font_color, int font_size, std::string string_value);
    
    void update(sf::Vector2i mouse_position, bool left_mouse_button);
    
    void draw(sf::RenderTarget* window);
    std::vector<Text> texts;
    std::vector<Button> buttons;
private:
    sf::RectangleShape table_body;
};