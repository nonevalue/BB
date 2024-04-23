#include "Button.hpp"

Button::Button(sf::Vector2f button_size, sf::Vector2f button_position, sf::Color button_color, sf::Font* font, sf::Color font_color, int font_size, std::string string_value)
{
    button_body.setSize(button_size);
    button_body.setPosition(button_position);
    button_body.setFillColor(button_color);
    button_body.setOutlineThickness(2.f);

    text.createText(font, font_color, font_size, button_position, string_value);
    text.setPosition(textPosition(button_size, button_position));
}

Button::Button(sf::Vector2f button_size, sf::Vector2f button_position, sf::Color button_color, float outline_thickness_value, sf::Color outline_color_value, sf::Color hover_color_value, sf::Color click_color_value, bool* return_pointer_value, sf::Font* font, sf::Color font_color, int font_size, std::string string_value)
{
    button_body.setSize(button_size);
    button_body.setPosition(button_position);
    button_body.setFillColor(button_color);
    button_body.setOutlineThickness(outline_thickness_value);

    setColor(outline_color_value, hover_color_value, click_color_value);

    text.createText(font, font_color, font_size, button_position, string_value);
    text.setPosition(textPosition(button_size, button_position));

    return_pointer = return_pointer_value;
}

void Button::setSize(sf::Vector2f button_size)
{
    button_body.setSize(button_size);
}

void Button::setPosition(sf::Vector2f button_position)
{
    button_body.setPosition(button_position);
}

void Button::setText(std::string string_value)
{
    text.setText(string_value);
}

void Button::setColor(sf::Color outline_color_value, sf::Color hover_color_value, sf::Color click_color_value)
{
    outline_color = outline_color_value;
    hover_color = hover_color_value;
    click_color = click_color_value;
}

void Button::setReturnPointer(bool* return_pointer_value)
{
    return_pointer = return_pointer_value;
}

void Button::update(sf::Vector2i cursor_position, bool left_mouse_click)
{
    if (!pressed)
    {
        button_body.setOutlineColor(outline_color);
        text.setColor(outline_color);
    }

    if (cursor_position.x > button_body.getPosition().x && cursor_position.x < button_body.getPosition().x + button_body.getSize().x)
    {
        if (cursor_position.y > button_body.getPosition().y && cursor_position.y < button_body.getPosition().y + button_body.getSize().y)
        {
            //Hover
            button_body.setOutlineColor(hover_color);
            text.setColor(hover_color);

            if (left_mouse_click)
            {
                pressed = true;
                //Click
                button_body.setOutlineColor(click_color);
                text.setColor(click_color);
            }
            if (pressed && !left_mouse_click)
            {
                //Release
                if (return_pointer != nullptr)
                {
                    *return_pointer = true;
                }
            }
        }
    }
    
    if (!left_mouse_click)
        pressed = false;
}

void Button::draw(sf::RenderTarget* window)
{
    window->draw(button_body);
    text.draw(window);
}

sf::Vector2f Button::textPosition(sf::Vector2f button_size, sf::Vector2f button_position)
{
    float x = 2 * button_position.x - text.getRect().left + (button_size.x - text.getRect().width) / 2;
    float y = 2 * button_position.y - text.getRect().top + (button_size.y - text.getRect().height) / 2;
    return sf::Vector2f(x, y);
}