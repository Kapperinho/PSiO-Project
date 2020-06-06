#include <iostream>
#include <vector>
#include <random>
#include <ctime>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "snake.h"
#include "fruit.h"

enum class Kierunek{
    UP,
    DOWN,
    RIGHT,
    LEFT
};

int SIZE = 30;
int vx = SIZE * SIZE;
int vy = SIZE * 15;
int h_lines = 30;
int v_lines = 15;
Kierunek kierunek = Kierunek::RIGHT;
int dlugosc = 3;



Fruit apple;


Snake snake[100];

void GameAction()
{
    for(int i=dlugosc; i>0; --i )
    {
        snake[i].x = snake[i-1].x;
        snake[i].y = snake[i-1].y;
    }

    switch (kierunek)
    {
        case Kierunek::RIGHT:
        snake[0].x ++ ;
        break;
        case Kierunek::LEFT:
        snake[0].x -- ;
        break;
        case Kierunek::UP:
        snake[0].y -- ;
        break;
        case Kierunek::DOWN:
        snake[0].y ++ ;
        break;
    }



    if((snake[0].x == apple.x) && (snake[0].y == apple.y))
    {
        dlugosc++;
        apple.x = rand() %30;
        apple.y = rand() %15;
    }

    if(snake[0].x > 30)
    {
        snake[0].x = 15;
        snake[0].y = 6;
        dlugosc = 3;
    }
    if(snake[0].y > 15)
    {
        snake[0].x = 15;
        snake[0].y = 6;
        dlugosc = 3;
    }

    if(snake[0].x < 0)
    {
        snake[0].x = 15;
        snake[0].y = 6;
        dlugosc = 3;
    }
    if(snake[0].y < 0)
    {
        snake[0].x = 15;
        snake[0].y = 6;
        dlugosc = 3;
    }

    for(int i =1; i < dlugosc; i++)
    {
        if(snake[0].x == snake[i].x  && snake[0].y == snake[i].y)
        {
            snake[0].x = 15;
            snake[0].y = 6;
            dlugosc = 3;
        }
    }
}

int main()
{
    srand(time(nullptr));
    sf::RenderWindow window(sf::VideoMode(vx, vy), "Snake");
    window.setFramerateLimit(10);
    sf::RectangleShape block;
    sf::RectangleShape blockSnake;
    sf::RectangleShape blockApple;

    block.setSize(sf::Vector2f(SIZE, SIZE));
    block.setFillColor(sf::Color::Black);
    block.setOutlineThickness(0);
    block.setOutlineColor(sf::Color::White);

    blockSnake.setSize(sf::Vector2f(SIZE, SIZE));
    blockSnake.setFillColor(sf::Color::Green);
    blockSnake.setOutlineThickness(0);
    blockSnake.setOutlineColor(sf::Color::White);

    blockApple.setSize(sf::Vector2f(SIZE, SIZE));
    blockApple.setFillColor(sf::Color::Red);
    blockApple.setOutlineThickness(1);
    blockApple.setOutlineColor(sf::Color::White);

    apple.x = rand() %30;
    apple.x = rand() %15;

    while(window.isOpen())
    {
        sf::Event event;
        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
            {
                window.close();
            }
            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Down)
                {
                    kierunek = Kierunek::DOWN;
                }
                if (event.key.code == sf::Keyboard::Left)
                {
                    kierunek = Kierunek::LEFT;
                }
                if (event.key.code == sf::Keyboard::Right)
                {
                    kierunek = Kierunek::RIGHT;
                }
                if (event.key.code == sf::Keyboard::Up)
                {
                    kierunek = Kierunek::UP;
                }
            }
        }

        GameAction();

        window.clear();
        for(int i=0; i < v_lines; i++)
            {
                for(int j=0; j < h_lines; j++)
                {
                    block.setPosition(j* SIZE,i* SIZE);
                    window.draw(block);
                }
            }
        for(int i= 0; i < dlugosc; i++)
        {
            blockSnake.setPosition(snake[i].x * SIZE, snake[i].y * SIZE);
            window.draw(blockSnake);
        }
        blockApple.setPosition(apple.x * SIZE, apple.y * SIZE);
        window.draw(blockApple);
        window.display();
    }

    return 0;
}
