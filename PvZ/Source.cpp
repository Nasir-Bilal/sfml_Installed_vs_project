#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace sf;
using namespace std;

class Game
{
private:
    RenderWindow window;
    RectangleShape redSquare;
    RectangleShape blueSquare;
    Clock clockForMovement;

public:
    // Constructor
    Game() : window(VideoMode(1000, 500), "SFML Collision Example")
    {
        window.setPosition(Vector2i(50, 50));

        // Initialize red square
        redSquare.setSize(Vector2f(100, 100));
        redSquare.setFillColor(Color::Red);
        redSquare.setPosition(300, 200);

        // Initialize blue square
        blueSquare.setSize(Vector2f(100, 100));
        blueSquare.setFillColor(Color::Blue);
        blueSquare.setPosition(600, 200);
    }

    // Main game loop
    void start()
    {
        while (window.isOpen())
        {
            Event event;

            // Poll for events
            while (window.pollEvent(event))
            {
                // Close window: exit
                if (event.type == Event::Closed || Keyboard::isKeyPressed(Keyboard::Escape))
                {
                    cout << "Exiting game" << endl;
                    window.close();
                }
            }

            window.clear();
            moveRedSquare();
            checkCollisions();
            renderDisplay();
            window.display();
        }
    }

    // Handle movement
    void moveRedSquare()
    {
        if (clockForMovement.getElapsedTime().asMilliseconds() > 10)
        {
            Vector2f pos = redSquare.getPosition();
            if (Keyboard::isKeyPressed(Keyboard::Up))
            {
                if (pos.y > 0)
                    pos.y -= 5;
            }
            if (Keyboard::isKeyPressed(Keyboard::Down))
            {
                if (pos.y + redSquare.getSize().y < window.getSize().y)
                    pos.y += 5;
            }
            if (Keyboard::isKeyPressed(Keyboard::Left))
            {
                if (pos.x > 0)
                    pos.x -= 5;
            }
            if (Keyboard::isKeyPressed(Keyboard::Right))
            {
                if (pos.x + redSquare.getSize().x < window.getSize().x)
                    pos.x += 5;
            }
            redSquare.setPosition(pos);
            clockForMovement.restart();
        }
    }


    // Check collisions
    void checkCollisions()
    {
        // Collision between red square and blue square
        FloatRect redBounds = redSquare.getGlobalBounds();
        FloatRect blueBounds = blueSquare.getGlobalBounds();

        if (redBounds.intersects(blueBounds))
        {
            cout << "Collision detected between red and blue squares" << endl;

            // Adjust the position based on the side of the collision
            if (redBounds.top < blueBounds.top && redBounds.top + redBounds.height > blueBounds.top) // Top collision
            {
                redSquare.setPosition(redBounds.left, blueBounds.top - redBounds.height);
            }
            else if (redBounds.top < blueBounds.top + blueBounds.height && redBounds.top + redBounds.height > blueBounds.top + blueBounds.height) // Bottom collision
            {
                redSquare.setPosition(redBounds.left, blueBounds.top + blueBounds.height);
            }
            else if (redBounds.left < blueBounds.left && redBounds.left + redBounds.width > blueBounds.left) // Left collision
            {
                redSquare.setPosition(blueBounds.left - redBounds.width, redBounds.top);
            }
            else if (redBounds.left < blueBounds.left + blueBounds.width && redBounds.left + redBounds.width > blueBounds.left + blueBounds.width) // Right collision
            {
                redSquare.setPosition(blueBounds.left + blueBounds.width, redBounds.top);
            }
        }

        // Collision between red square and window walls
        Vector2f pos = redSquare.getPosition();
        if (pos.x < 0)
            pos.x = 0;
        if (pos.x + redSquare.getSize().x > window.getSize().x)
            pos.x = window.getSize().x - redSquare.getSize().x;
        if (pos.y < 0)
            pos.y = 0;
        if (pos.y + redSquare.getSize().y > window.getSize().y)
            pos.y = window.getSize().y - redSquare.getSize().y;
        redSquare.setPosition(pos);
    }


    // Render shapes
    void renderDisplay()
    {
        window.draw(redSquare);
        window.draw(blueSquare);
    }
};

int main()
{
    Game game;
    game.start();
    return 0;
}
