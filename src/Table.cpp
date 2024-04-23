#include "Table.hpp"

Table::Table()
{

}

Table::Table(sf::Vector2f position, sf::Vector2f size, sf::Color table_color)
{
    table_body.setPosition(position);
    table_body.setSize(size);
    table_body.setFillColor(table_color);
}

void Table::create(sf::Vector2f position, sf::Vector2f size, sf::Color table_color)
{
    table_body.setPosition(position);
    table_body.setSize(size);
    table_body.setFillColor(table_color);
}

void Table::addText(sf::Font* font, sf::Color font_color, int font_size, sf::Vector2f position_value, std::string string_value)
{
    position_value.x += table_body.getPosition().x;
    position_value.y += table_body.getPosition().y;
    Text temp_text;
    temp_text.createText(font, font_color, font_size, position_value, string_value);
    texts.push_back(temp_text);
}

void Table::addButton(sf::Vector2f button_size, sf::Vector2f button_position, sf::Color button_color, float outline_thickness_value, sf::Color outline_color_value, sf::Color hover_color_value, sf::Color click_color_value, bool* return_pointer_value, sf::Font* font, sf::Color font_color, int font_size, std::string string_value)
{
    button_position.x += table_body.getPosition().x;
    button_position.y += table_body.getPosition().y;
    Button temp_button(button_size, button_position, button_color, outline_thickness_value, outline_color_value, hover_color_value, click_color_value, return_pointer_value, font, font_color, font_size, string_value);
    buttons.push_back(temp_button);
}

void Table::update(sf::Vector2i mouse_position, bool left_mouse_button)
{
    for (int i = 0; i < buttons.size(); i++)
    {
        buttons[i].update(mouse_position, left_mouse_button);
    }
}

void Table::draw(sf::RenderTarget* window)
{
    window->draw(table_body);

    for (int i = 0; i < texts.size(); i++)
        texts[i].draw(window);

    for (int i = 0; i < buttons.size(); i++)
        buttons[i].draw(window);
    
}