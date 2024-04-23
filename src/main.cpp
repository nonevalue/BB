#include "Game.hpp"

int main()
{
    Game game;
    return 0;
}

/*
#include <iostream>
#include <sstream>

#include <SFML/Graphics.hpp>
#include "Bullet.hpp"
//#include "Enemy.hpp"

#include "Table.hpp"

template <typename T>
std::string toString(T arg)
{
    std::stringstream ss;
    ss << arg;
    return ss.str();
}

int main()
{
    //random number generator
    srand(time(NULL));

    //window  
    sf::RenderWindow window(sf::VideoMode(600, 600), "Big Ball throw Balls to Big Balls");
    window.setFramerateLimit(60);

    //window icon
    sf::Image icon;
    icon.loadFromFile("./icon.png");
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    //cursor
    sf::Cursor cross;
    cross.loadFromSystem(sf::Cursor::Cross);
    sf::Cursor arrow;
    arrow.loadFromSystem(sf::Cursor::Arrow);
    window.setMouseCursor(arrow);

    //font
    sf::Font font;
    font.loadFromFile("./font.ttf");

    //system
    bool left_mouse_click = false;
    bool up = false, down = false, left = false, right = false;

    int shoot_timer = 60, base_shoot_time = 60;

    int ammo = 60;
    int score = 0;
    int totalscore = 0;
    int health = 3;
    float move_speed = 3.f;
    
    int enemy_level = 1;

    //Player
    sf::CircleShape player(20.f);
    player.setOrigin(20.f, 20.f);
    player.setPosition(300, 300);
    player.setFillColor(sf::Color::Green);
    player.setOutlineThickness(2.f);
    player.setOutlineColor(sf::Color::Black);

    //bullet
    Bullet bullet;
    std::vector<Bullet> bullets;
    int bullet_health = 1;

    //main menu
    bool main_menu_open = true;
    Table main_menu(sf::Vector2f(0.f, 0.f), sf::Vector2f(600.f, 600.f), sf::Color(230, 230, 230));
    
    main_menu.addText(&font, sf::Color::Black, 40, sf::Vector2f(75.f, 100.f), "Big Ball throw Balls");
    main_menu.addText(&font, sf::Color::Black, 50, sf::Vector2f(125.f, 150.f), "to Big Balls");
    main_menu.addText(&font, sf::Color::Black, 20, sf::Vector2f(264.f, 220.f), "REMAKE");
    bool new_game_button = false;
    main_menu.addButton(sf::Vector2f(400.f, 150.f), sf::Vector2f(100.f, 300.f), sf::Color::White, 3, sf::Color::Black, sf::Color::Red, sf::Color::Green, &new_game_button, &font, sf::Color::Black, 41, "New Game");

    //game menu
    bool game_menu_open = false;
    Table game_menu_background(sf::Vector2f(0.f, 0.f), sf::Vector2f(600.f, 600.f), sf::Color(50, 50, 50, 127));
    Table game_menu(sf::Vector2f(150.f, 200.f), sf::Vector2f(300.f, 260.f), sf::Color::White);
    
    game_menu.addText(&font, sf::Color::Black, 40, sf::Vector2f(80.f, 20.f), "Paused");
    game_menu.addText(&font, sf::Color::Black, 18, sf::Vector2f(7.f, 70.f), "(press esc for resume owo)");
    bool restart_button = false;
    game_menu.addButton(sf::Vector2f(200.f, 50.f), sf::Vector2f(50.f, 115.f), sf::Color::White, 3, sf::Color::Black, sf::Color::Red, sf::Color::Green, &restart_button, &font, sf::Color::Black, 40, "reset");
    bool main_menu_button = false;
    game_menu.addButton(sf::Vector2f(200.f, 50.f), sf::Vector2f(50.f, 185.f), sf::Color::White, 3, sf::Color::Black, sf::Color::Red, sf::Color::Green, &main_menu_button, &font, sf::Color::Black, 31, "main menu");

    //game interface
    Text ammo_text(&font, sf::Color::Black, 40, sf::Vector2f(430.f, 0.f), "ammo:"+ toString<int>(ammo));
    Text score_text(&font, sf::Color::Black, 40, sf::Vector2f(0.f, 0.f), "score:"+ toString<int>(score));
    Text health_text(&font, sf::Color::Black, 40, sf::Vector2f(0.f, 530.f), "health:"+ toString<int>(health));
    
    Text total_score_text(&font, sf::Color::Black, 20, sf::Vector2f(0.f, 50.f), "total score:"+ toString<int>(totalscore));
    Text enemy_level_text(&font, sf::Color::Black, 20, sf::Vector2f(0.f, 80.f), "enemy level:"+ toString<int>(enemy_level));

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                    left_mouse_click = true;
            }
            if (event.type == sf::Event::MouseButtonReleased)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                    left_mouse_click = false;
            }
            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Escape)
                {
                    if (!main_menu_open)
                    {
                        if (game_menu_open)
                        {
                            window.setMouseCursor(cross);
                            game_menu_open = false;
                        }
                        else
                        {
                            window.setMouseCursor(arrow);
                            game_menu_open = true;
                        }
                    }
                }
                if (event.key.code == sf::Keyboard::W)
                    up = true;
                if (event.key.code == sf::Keyboard::S)
                    down = true;
                if (event.key.code == sf::Keyboard::A)
                    left = true;
                if (event.key.code == sf::Keyboard::D)
                    right = true;
            }
            if (event.type == sf::Event::KeyReleased)
            {
                if (event.key.code == sf::Keyboard::W)
                    up = false;
                if (event.key.code == sf::Keyboard::S)
                    down = false;
                if (event.key.code == sf::Keyboard::A)
                    left = false;
                if (event.key.code == sf::Keyboard::D)
                    right = false;
            }
            
        }

        if (main_menu_open)
        {
            main_menu.update(sf::Mouse::getPosition(window), left_mouse_click);
            if (new_game_button)
            {
                new_game_button = false;
                main_menu_open = false;
                if (!game_menu_open)
                {
                    window.setMouseCursor(cross);
                }
            }
        }
        else
        {
            if (game_menu_open)
            {
                game_menu.update(sf::Mouse::getPosition(window), left_mouse_click);
                if (main_menu_button)
                {
                    main_menu_button = false;
                    main_menu_open = true;
                }
            }
            else
            {
                if (shoot_timer > 0)
                    shoot_timer--;
                if (left_mouse_click && shoot_timer == 0 && ammo > 0)
                {
                    ammo--;
                    ammo_text.setText("ammo:"+ toString<int>(ammo));
                    shoot_timer = base_shoot_time;
                    bullet.resetBullet(player.getPosition(), sf::Mouse::getPosition(window), bullet_health);
                    bullets.push_back(bullet);
                }

                if (up)
                    player.move(sf::Vector2f(0, -move_speed));
                if (down)
                    player.move(sf::Vector2f(0, move_speed));
                if (left)
                    player.move(sf::Vector2f(-move_speed, 0));
                if (right)
                    player.move(sf::Vector2f(move_speed, 0));

                for (int i = 0; i < bullets.size(); i++)
                {
                    bullets[i].update();
                    if (bullets[i].isOutside())
                    {
                        bullets.erase(bullets.begin() + i, bullets.begin() + i + 1);
                        i--;
                    }
                }
            }
        }
        

        window.clear(sf::Color(230, 230, 230));
        
        if (main_menu_open)
            main_menu.draw(&window);
        else
        {
            window.draw(player);
            
            health_text.draw(&window);
            ammo_text.draw(&window);
            score_text.draw(&window);
            total_score_text.draw(&window);
            enemy_level_text.draw(&window);

            for (int i = 0; i < bullets.size(); i++)
                bullets[i].draw(&window);

            if (game_menu_open)
            {
                game_menu_background.draw(&window);
                game_menu.draw(&window);
            }
        }
        window.display();
    }

    return 0;
}

*/