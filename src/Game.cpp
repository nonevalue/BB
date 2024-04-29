#include "Game.hpp"

Game::Game()
{
    initWindow();
    initVariables();
    initTables();

    while (window.isOpen())
    {
        update();
        draw();
    }
}

void Game::initWindow()
{
    window.create(sf::VideoMode(600, 600), "Big Ball throw Balls to Big Balls");
    window.setFramerateLimit(60);

    icon.loadFromFile("./icon.png");
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    
    cross.loadFromSystem(sf::Cursor::Cross);
    arrow.loadFromSystem(sf::Cursor::Arrow);
    window.setMouseCursor(arrow);

    font.loadFromFile("./font.ttf");
}

void Game::initVariables()
{
    //GAME VARIABLES

    //<-------Player Variables------->
    //System
    left_mouse_click = false;
    up = false, down = false, left = false, right = false;

    shoot_timer = 0, base_shoot_time = 60;
    reload_timer = 0, base_reload_time = 360;
    
    ammo = 60;
    score = 0;
    total_score = 0;
    health = 3;
    move_speed = 3.f;

    
    //Upgrades
    upgrade = 300;
    player_level = 1;

    bullet_health = 1;
    shoot_time_level = 1;
    reload_time = 6;
    auto_heal = false;
    auto_reload = false;

    bullet.setHealth(bullet_health);
    //<------------------------------>
    
    //Enemy system variables
    enemy_level = 1;
    enemy_spawn_timer = 0;
    enemy_spawn_time = 90;
    enemy_level_counter = 0;

    enemy.setHealth(1);
    enemy.setColor(sf::Color::Red);
    //<-------Table Variables------->
    main_menu_open = true;
    new_game_button = false;

    game_menu_open = false;
    reset_button = false;
    main_menu_button = false;

    upgrade_menu_open = true;
}

void Game::initTables()
{
    //Main Menu
    main_menu.create(sf::Vector2f(0.f, 0.f), sf::Vector2f(600.f, 600.f), sf::Color(230, 230, 230));

    main_menu.addText(&font, sf::Color::Black, 40, sf::Vector2f(75.f, 100.f), "Big Ball throw Balls");
    main_menu.addText(&font, sf::Color::Black, 50, sf::Vector2f(125.f, 150.f), "to Big Balls");
    main_menu.addText(&font, sf::Color::Black, 20, sf::Vector2f(264.f, 220.f), "REMAKE");

    main_menu.addButton(sf::Vector2f(400.f, 150.f), sf::Vector2f(100.f, 300.f), sf::Color::White, 3, sf::Color::Black, sf::Color::Red, sf::Color::Green, &new_game_button, &font, sf::Color::Black, 41, "New Game");

    //Game Menu
    game_menu_background.create(sf::Vector2f(0.f, 0.f), sf::Vector2f(600.f, 600.f), sf::Color(50, 50, 50, 127));
    game_menu.create(sf::Vector2f(150.f, 200.f), sf::Vector2f(300.f, 260.f), sf::Color::White);

    game_menu.addText(&font, sf::Color::Black, 40, sf::Vector2f(80.f, 20.f), "Paused");
    game_menu.addText(&font, sf::Color::Black, 18, sf::Vector2f(7.f, 70.f), "(press esc for resume owo)");

    game_menu.addButton(sf::Vector2f(200.f, 50.f), sf::Vector2f(50.f, 115.f), sf::Color::White, 3, sf::Color::Black, sf::Color::Red, sf::Color::Green, &reset_button, &font, sf::Color::Black, 40, "reset");
    game_menu.addButton(sf::Vector2f(200.f, 50.f), sf::Vector2f(50.f, 185.f), sf::Color::White, 3, sf::Color::Black, sf::Color::Red, sf::Color::Green, &main_menu_button, &font, sf::Color::Black, 31, "main menu");

    //game interface
    ammo_text.createText(&font, sf::Color::Black, 40, sf::Vector2f(430.f, 0.f), "ammo:"+ toString<int>(ammo));
    score_text.createText(&font, sf::Color::Black, 40, sf::Vector2f(0.f, 0.f), "score:"+ toString<int>(score));
    health_text.createText(&font, sf::Color::Black, 40, sf::Vector2f(0.f, 530.f), "health:"+ toString<int>(health));
    
    total_score_text.createText(&font, sf::Color::Black, 20, sf::Vector2f(0.f, 50.f), "total score:"+ toString<int>(total_score));
    enemy_level_text.createText(&font, sf::Color::Black, 20, sf::Vector2f(0.f, 80.f), "enemy level:"+ toString<int>(enemy_level));

    //upgrade menu
    upgrade_menu.create(sf::Vector2f(380, 390), sf::Vector2f(220, 190), sf::Color::Transparent);

    upgrade_menu.addText(&font, sf::Color::Black, 25, sf::Vector2f(10.f, 10.f), "Stats");
    upgrade_menu.addText(&font, sf::Color::Black, 20, sf::Vector2f(10.f, 40.f), "1-bullet power:"+toString<int>(bullet_health));
    upgrade_menu.addText(&font, sf::Color::Black, 20, sf::Vector2f(10.f, 65.f), "2-bullet/s:"+toString<float>(shoot_time_level));
    upgrade_menu.addText(&font, sf::Color::Black, 20, sf::Vector2f(10.f, 90.f), "3-reload speed:"+toString<int>(reload_time)+"s");
    upgrade_menu.addText(&font, sf::Color::Black, 20, sf::Vector2f(10.f, 115.f), "4-auto heal: -");
    upgrade_menu.addText(&font, sf::Color::Black, 20, sf::Vector2f(10.f, 140.f), "5-auto reload: -");
    upgrade_menu.addText(&font, sf::Color::Black, 14, sf::Vector2f(10.f, 165.f), "next upgrade:"+toString<int>(upgrade*player_level)+"score");

    bullet_power_text = &upgrade_menu.texts[1];
    bullet_rate_text = &upgrade_menu.texts[2];
    reload_speed_text = &upgrade_menu.texts[3];
    auto_health_text = &upgrade_menu.texts[4];
    auto_reload_text = &upgrade_menu.texts[5];
    next_upgrade_text = &upgrade_menu.texts[6];
}

void Game::resetGame()
{
    //RESETING VARIABLES

    //<-------Player Variables------->
    //System
    left_mouse_click = false;
    up = false, down = false, left = false, right = false;

    shoot_timer = 60, base_shoot_time = 60;
    reload_timer = 0, base_reload_time = 360;
    
    ammo = 60;
    score = 0;
    total_score = 0;
    health = 3;
    move_speed = 3.f;

    
    //Upgrades
    upgrade = 300;
    player_level = 1;

    bullet_health = 1;
    shoot_time_level = 1;
    reload_time = 6;
    auto_heal = false;
    auto_reload = false;
    
    bullet.setHealth(bullet_health);
    //<------------------------------>
    
    //Enemy system variables
    enemy_level = 1;
    enemy_spawn_timer = 0;
    enemy_spawn_time = 90;
    enemy_level_counter = 0;

    enemy.setHealth(1);
    enemy.setColor(sf::Color::Red);

    //RESETING ARRAYS
    enemies.clear();
    bullets.clear();

    //RESETING OBJECTS

    player.setPosition(sf::Vector2f(300, 300));

    //RESETING TABLES AND TEXTS
    ammo_text.setText("ammo:"+ toString<int>(ammo));
    score_text.setText("score:"+ toString<int>(score));
    health_text.setText("health:"+ toString<int>(health));

    total_score_text.setText("total score:"+ toString<int>(total_score));
    enemy_level_text.setText("enemy level:"+ toString<int>(enemy_level));

    bullet_power_text->setText("1-bullet power:"+toString<int>(bullet_health));
    bullet_rate_text->setText("2-bullet/s:"+toString<float>(shoot_time_level));
    reload_speed_text->setText("3-reload speed:"+toString<int>(reload_time)+"s");
    auto_health_text->setText("4-auto heal: -");
    auto_reload_text->setText("5-auto reload: -");
}

void Game::update()
{
    updateEvents();
    if (main_menu_open)
        updateMainMenu();
    else
    {
        if (game_menu_open)
            updateGameMenu();
        else
            updateGame();
    }
}

void Game::updateEvents()
{
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
            
            if (!main_menu_open && !game_menu_open)
            {
                if (event.key.code == sf::Keyboard::W)
                    up = true;
                if (event.key.code == sf::Keyboard::S)
                    down = true;
                if (event.key.code == sf::Keyboard::A)
                    left = true;
                if (event.key.code == sf::Keyboard::D)
                    right = true;

                if (event.key.code == sf::Keyboard::R && reload_timer == 0 && score >= 60)
                {
                    reload_timer = base_reload_time;
                    ammo = 60;
                    score -= 60;

                    score_text.setText("score:"+toString<int>(score));
                    ammo_text.setText("reloading");
                    ammo_text.setPosition(sf::Vector2f(380.f, 0.f));
                }
                if (event.key.code == sf::Keyboard::Q && score >= 100)
                {
                    health++;
                    score -= 100;

                    score_text.setText("score:"+toString<int>(score));
                    health_text.setText("health:"+ toString<int>(health));
                }
                
                if (event.key.code == sf::Keyboard::C)
                {
                    if (upgrade_menu_open)
                        upgrade_menu_open = false;
                    else
                        upgrade_menu_open = true;
                }
                
                if (upgrade_menu_open)
                {
                    if (event.key.code == sf::Keyboard::Num1 && score >= player_level * upgrade)
                    {
                        bullet_health++;
                        score -= upgrade * player_level;
                        player_level++;

                        score_text.setText("score:"+toString<int>(score));
                        bullet_power_text->setText("1-bullet power:"+toString<int>(bullet_health));
                        next_upgrade_text->setText("next upgrade:"+toString<int>(upgrade * player_level)+"score");
                    }
                    if (event.key.code == sf::Keyboard::Num2 && score >= player_level * upgrade && shoot_time_level < 60)
                    {
                        shoot_time_level++;
                        base_shoot_time = 60 / shoot_time_level;

                        score -= upgrade * player_level;
                        player_level++;

                        score_text.setText("score:"+toString<int>(score));
                        bullet_rate_text->setText("2-bullet/s:"+toString<float>(shoot_time_level));
                        next_upgrade_text->setText("next upgrade:"+toString<int>(upgrade * player_level)+"score");
                    }
                    if (event.key.code == sf::Keyboard::Num3 && score >= player_level * upgrade && reload_time > 0)
                    {
                        reload_time -= 2;
                        base_reload_time = reload_time * 60 + 1;

                        score -= upgrade * player_level;
                        player_level++;

                        score_text.setText("score:"+toString<int>(score));
                        reload_speed_text->setText("3-reload speed:"+toString<int>(reload_time)+"s");
                        next_upgrade_text->setText("next upgrade:"+toString<int>(upgrade * player_level)+"score");
                    }
                    if (event.key.code == sf::Keyboard::Num4 && score >= player_level * upgrade && !auto_heal)
                    {
                        auto_heal = true;

                        score -= upgrade * player_level;
                        player_level++;

                        score_text.setText("score:"+toString<int>(score));
                        auto_health_text->setText("4-auto heal: +");
                        next_upgrade_text->setText("next upgrade:"+toString<int>(upgrade * player_level)+"score");
                    }
                    if (event.key.code == sf::Keyboard::Num5 && score >= player_level * upgrade && !auto_reload)
                    {
                        auto_reload = true;

                        score -= upgrade * player_level;
                        player_level++;

                        score_text.setText("score:"+toString<int>(score));
                        auto_reload_text->setText("5-auto reload: +");
                        next_upgrade_text->setText("next upgrade:"+toString<int>(upgrade * player_level)+"score");
                    }
                }
            }
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
}

void Game::updateMainMenu()
{
    main_menu.update(sf::Mouse::getPosition(window), left_mouse_click);
    if (new_game_button)
    {
        new_game_button = false;
        main_menu_open = false;
        if (!game_menu_open)
            window.setMouseCursor(cross);
    }
}

void Game::updateGameMenu()
{
    game_menu.update(sf::Mouse::getPosition(window), left_mouse_click);
    if (main_menu_button)
    {
        main_menu_button = false;
        main_menu_open = true;
    }
    if (reset_button)
    {
        reset_button = false;
        resetGame();
    }
}

void Game::updateGame()
{
    if (auto_reload && ammo == 0 && score >= 60)
    {
        reload_timer = base_reload_time;
        ammo = 60;
        score -= 60;
        score_text.setText("score:"+toString<int>(score));
        ammo_text.setText("reloading");
        ammo_text.setPosition(sf::Vector2f(380.f, 0.f));
    }

    if (shoot_timer >= 1)
        shoot_timer--;

    if (reload_timer > 0)
    {
        reload_timer--;
        if (reload_timer == 0)
        {
            ammo_text.setText("ammo:"+ toString<int>(ammo));
            ammo_text.setPosition(sf::Vector2f(430.f, 0.f));
        }
    }

    if (left_mouse_click && shoot_timer < 1 && reload_timer == 0 && ammo > 0)
    {
        ammo--;
        ammo_text.setText("ammo:"+ toString<int>(ammo));
        shoot_timer += base_shoot_time;
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
    
    player.update(sf::Mouse::getPosition(window));

    updateBullets();
    updateEnemies();
}

void Game::updateBullets()
{
    for (int i = 0; i < bullets.size(); i++)
    {
        bullets[i].update();

        if (bullets[i].isOutside())
        {
            bullets.erase(bullets.begin() + i, bullets.begin() + i + 1);
            i--;
            continue;
        }

        for (int j = 0; j < enemies.size(); j++)
        {
            sf::Vector2f distance = bullets[i].getPosition() - enemies[j].getPosition();
            float hypotenuse = sqrt(pow(distance.x,2) + pow(distance.y,2));

            if (hypotenuse <= bullets[i].getRadius() + enemies[j].getRadius())
            {
                if (bullets[i].getHealth() > enemies[j].getHealth())
                {
                    bullets[i].setHealth(bullets[i].getHealth() - enemies[j].getHealth());
                    enemies.erase(enemies.begin() + j, enemies.begin() + j + 1);
                    j--;

                    loot();
                }
                else if (bullets[i].getHealth() < enemies[j].getHealth())
                {
                    enemies[j].setHealth(enemies[j].getHealth() - bullets[i].getHealth());
                    bullets.erase(bullets.begin() + i, bullets.begin() + i + 1);
                    i--;
                }
                else
                {
                    bullets.erase(bullets.begin() + i, bullets.begin() + i + 1);
                    i--;
                    enemies.erase(enemies.begin() + j, enemies.begin() + j + 1);
                    j--;

                    loot();
                }
            }
        }
    }
}

void Game::updateEnemies()
{
    for (int i = 0; i < enemies.size(); i++)
    {
        enemies[i].update(player.getPosition());
        
        sf::Vector2f distance = enemies[i].getPosition() - player.getPosition();
        float hypotenuse = sqrt(pow(distance.x, 2) + pow(distance.y, 2));

        if (hypotenuse < enemy.getRadius() + player.getRadius())
        {
            enemies.erase(enemies.begin() + i, enemies.begin() + i + 1);
            i--;
            if (health == 1 && auto_heal && score >= 100)
            {
                score -= 100;
                score_text.setText("score:"+toString<int>(score));
            }
            else
            {
                health--;
                health_text.setText("health:"+ toString<int>(health));
                if (health <= 0)
                {
                    resetGame();
                    game_menu_open = true;
                }
            }
        }
    }
    
    enemy_spawn_timer++;
    if (enemy_spawn_timer == enemy_spawn_time)
    {
        enemy_spawn_timer = 0;
        enemy_level_counter++;

        enemy.randomizePosition(player.getPosition());
        enemies.push_back(enemy);
    }
    if (enemy_level_counter == 30)
    {
        enemy_level_counter = 0;
        enemy_level++;
        enemy.setHealth(enemy_level);
        enemy.setColor(sf::Color(rand()%255, rand()%255, rand()%255));

        if (enemy_level > 6 && enemy_level <= 10)
            enemy_spawn_time -= 15;

        enemy_level_text.setText("enemy level:"+ toString<int>(enemy_level));
    }
    
}

void Game::loot()
{
    score += 20 * enemy_level;
    total_score += 20 * enemy_level;
    score_text.setText("score:"+ toString<int>(score));
    total_score_text.setText("total score:"+ toString<int>(total_score));
}

void Game::draw()
{
    window.clear(sf::Color(200, 200, 200));
        
    if (main_menu_open)
        main_menu.draw(&window);
    else
    {
        player.draw(&window);

        for (int i = 0; i < bullets.size(); i++)
            bullets[i].draw(&window);

        for (int i = 0; i < enemies.size(); i++)
            enemies[i].draw(&window);

            health_text.draw(&window);
            ammo_text.draw(&window);
            score_text.draw(&window);
            total_score_text.draw(&window);
            enemy_level_text.draw(&window);

        if (upgrade_menu_open)
            upgrade_menu.draw(&window);

        if (game_menu_open)
        {
            game_menu_background.draw(&window);
            game_menu.draw(&window);
        }
    }
    window.display();
}

