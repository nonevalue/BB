#pragma once

#include <iostream>
#include <sstream>

#include <SFML/Graphics.hpp>

#include "Table.hpp"

#include "Player.hpp"
#include "Bullet.hpp"


template <typename T>
std::string toString(T arg)
{
    std::stringstream ss;
    ss << arg;
    return ss.str();
}

class Game
{
public:
    Game();
private:
    void initWindow();
    void initVariables();
    void initTables();
    void resetGame();
    
    void update();
    void updateEvents();
    
    void updateMainMenu();
    void updateGameMenu();
    void updateGame();

    void draw();

    //Window  
    sf::RenderWindow window;
    sf::Image icon;
    sf::Cursor cross;
    sf::Cursor arrow;
    sf::Event event;

    //Font
    sf::Font font;

    //System
    bool left_mouse_click;
    bool up, down, left, right;

    int shoot_timer, base_shoot_time;

    int ammo;
    int score;
    int totalscore;
    int health;
    float move_speed;
    
    int enemy_level;

    //Player
    Player player;

    //Bullet
    Bullet bullet;
    std::vector<Bullet> bullets;
    int bullet_health;

    //<-----Tables----->

    //Main Menu
    bool main_menu_open;
    Table main_menu;

    bool new_game_button;

    //Game Menu
    bool game_menu_open;
    Table game_menu_background;
    Table game_menu;

    bool reset_button;
    bool main_menu_button;

    //Game Interface
    Text ammo_text;
    Text score_text;
    Text health_text;
    Text total_score_text;
    Text enemy_level_text;
};
