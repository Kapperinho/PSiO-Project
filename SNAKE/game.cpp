#include "game.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>

Game::Game() : window_(sf::VideoMode(vx, vy), "Snake")
{
    window_.setFramerateLimit(10);

    font_.loadFromFile("Arimo-Regular.ttf");

    wallTexture_.loadFromFile("wall.png");
    backgroundTexture_.loadFromFile("grass.png");
    heartTexture_.loadFromFile("heart.png");
    titleTexture_.loadFromFile("logo.png");

    block_.setSize(sf::Vector2f(SIZE, SIZE));
    block_.setTexture(&backgroundTexture_);

    apple_.setX(rand() %30);
    apple_.setY(rand() %15);

    std::string path{};
    switch (rand() % 3)
    {
    case 0:
        path = "map1.txt";
        break;
    case 1:
        path = "map2.txt";
        break;
    case 2:
        path = "map3.txt";
        break;
    }

    std::vector<std::string> mapInChars;
    if(!path.empty())
    {
        std::fstream map(path, std::ios::in);
        if(map.is_open())
        {
            while(!map.eof())
            {
                std::string line;
                map >> line;
                mapInChars.push_back(line);
            }
        }
    }

    for(size_t i = 0; i < mapInChars.size(); i++)
    {
        for(size_t j = 0; j < mapInChars[i].size(); j++)
        {
            if(mapInChars[i][j] == '#') map_.emplace_back(j, i, &wallTexture_);
        }
    }

    snake_[0].setFillColor(sf::Color::Blue);

    for(int i = 0; i < 3; i++){
        hearts_.emplace_back();
        hearts_.back().setTexture(&heartTexture_);
        hearts_.back().setSize(sf::Vector2f(SIZE, SIZE));

    }

    hearts_[0].setPosition(0, 0);
    hearts_[1].setPosition(SIZE, 0);
    hearts_[2].setPosition(2 * SIZE, 0);
}

void Game::start()
{
    menu();
    while(window_.isOpen())
    {
        std::string s = std::to_string(points_);
        std::string tekst = "Score : "+ s;
        sf::Text text(tekst,font_);
        text.setCharacterSize(35);
        text.setPosition(700,30);
        sf::Event event;
        while(window_.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
            {
                window_.close();
            }
            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Down)
                {
                    dir_ = Kierunek::DOWN;
                }
                if (event.key.code == sf::Keyboard::Left)
                {
                    dir_ = Kierunek::LEFT;
                }
                if (event.key.code == sf::Keyboard::Right)
                {
                    dir_ = Kierunek::RIGHT;
                }
                if (event.key.code == sf::Keyboard::Up)
                {
                    dir_ = Kierunek::UP;
                }
            }
        }

        GameAction();
        if(hearts_.size() == 0){
            window_.close();
            std::cout << "GAME OVER" << std::endl;
        }
        window_.clear();
        for(int i=0; i < v_lines; i++)
        {
            for(int j=0; j < h_lines; j++)
            {
                block_.setPosition(j* SIZE,i* SIZE);
                window_.draw(block_);
            }
        }
        for(const auto& wall : map_)
        {
            window_.draw(wall);
        }
        for(int i= 0; i < snakeLength_; i++)
        {
            snake_[i].setActualPos();
            window_.draw(snake_[i]);
        }
        apple_.setPosition(apple_.getX() * SIZE, apple_.getY() * SIZE);
        window_.draw(apple_);
        window_.draw(text);
        for(const auto& heart : hearts_){
            window_.draw(heart);
        }
        window_.display();
    }
}

void Game::GameAction()
{
    for(int i=snakeLength_; i>0; --i )
    {
        snake_[i].setCoordinates(snake_[i-1].getX(), snake_[i-1].getY());
    }

    switch (dir_)
    {
    case Kierunek::RIGHT:
        snake_[0].setX(snake_[0].getX() + 1);
        break;
    case Kierunek::LEFT:
        snake_[0].setX(snake_[0].getX() - 1);
        break;
    case Kierunek::UP:
        snake_[0].setY(snake_[0].getY() - 1);
        break;
    case Kierunek::DOWN:
        snake_[0].setY(snake_[0].getY() + 1);
        break;
    }

    if(snake_[0].getGlobalBounds().intersects(apple_.getGlobalBounds()))
    {
        snakeLength_++;
        points_ += 10;
        int x, y;

        auto checkCoordsWithWall = [&](){
            for(const auto& wall : map_){
                if(wall.getX() == x && wall.getY() == y){
                    return true;
                }
            }
            return false;
        };

        do{
            x = rand() % 30;
            y = rand() % 15;
        }while(checkCoordsWithWall());
        apple_.setX(x);
        apple_.setY(y);
    }

    if(snake_[0].getX() >= 30 || snake_[0].getY() >= 15 || snake_[0].getX() < 0 || snake_[0].getY() < 0)
    {
        snake_[0].setStartPos();
        snakeLength_ = 3;
        points_ = 0;
        hearts_.erase(hearts_.end() - 1);
    }

    for(int i =1; i < snakeLength_; i++)
    {
        if(snake_[0].getX() == snake_[i].getX()  && snake_[0].getY() == snake_[i].getY())
        {
            snake_[0].setStartPos();
            snakeLength_ = 3;
            points_ = 0;
            hearts_.erase(hearts_.end() - 1);
        }
    }

    for(const auto& wall : map_)
    {
        if(wall.getGlobalBounds().intersects(snake_[0].getGlobalBounds()))
        {
            snake_[0].setStartPos();
            snakeLength_ = 3;
            points_ = 0;
            hearts_.erase(hearts_.end() - 1);
        }
    }
}

void Game::menu()
{
    sf::RectangleShape startButton;
    startButton.setSize(sf::Vector2f(300, 150));
    startButton.setOrigin(startButton.getSize() / 2.0f);
    startButton.setPosition(vx / 2, vy / 2 + 60);
    startButton.setFillColor(sf::Color::Red);

    sf::Text startButtonText;
    startButtonText.setFont(font_);
    startButtonText.setString("Start");
    startButtonText.setCharacterSize(80);
    startButtonText.setFillColor(sf::Color::White);
    startButtonText.setPosition(vx / 2 - 85, vy / 2 + 5);

    sf::RectangleShape title;
    title.setSize(sf::Vector2f(400, 200));
    title.setPosition(290, 0);
    title.setTexture(&titleTexture_);

    while(window_.isOpen())
    {
        sf::Event event;
        while(window_.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
            {
                window_.close();
            }
            else if(event.type == sf::Event::MouseButtonPressed)
            {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window_);
                if(startButton.getGlobalBounds().contains(mousePos.x, mousePos.y)){
                    return;
                }
            }
        }
        window_.clear();
        window_.draw(startButton);
        window_.draw(startButtonText);
        window_.draw(title);
        window_.display();
    }
}
