#pragma once

#include <iostream>
#include <sstream>

#include <SFML/Graphics.hpp>

#include "Table.hpp"

#include "Player.hpp"
#include "Bullet.hpp"
#include "Enemy.hpp"


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
    void updateBullets();
    void updateEnemies();
    void loot();

    void draw();

    //Window  
    sf::RenderWindow window;
    sf::Image icon;
    sf::Cursor cross;
    sf::Cursor arrow;
    sf::Event event;

    //Font
    sf::Font font;

    //<-------Player Variables------->
    //System
    bool left_mouse_click;
    bool up, down, left, right;

    float shoot_timer, base_shoot_time;
    int reload_timer, base_reload_time;

    int ammo;
    int score;
    int total_score;
    int health;
    float move_speed;

    //Upgrades
    int upgrade;
    int player_level;

    int bullet_health;
    float shoot_time_level;
    int reload_time;
    bool auto_heal;
    bool auto_reload;
    //<------------------------------>
    
    //Enemy system variables
    int enemy_level;
    int enemy_spawn_timer;
    int enemy_spawn_time;
    int enemy_level_counter;

    //Player
    Player player;

    //Bullet
    Bullet bullet;
    std::vector<Bullet> bullets;

    //Enemies

    Enemy enemy;
    std::vector<Enemy> enemies;

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

    //Upgrade Menu
    bool upgrade_menu_open;
    Table upgrade_menu;
    Text* bullet_power_text;
    Text* bullet_rate_text;
    Text* reload_speed_text;
    Text* auto_health_text;
    Text* auto_reload_text;
    Text* next_upgrade_text;
};
