#include <iostream>
#include <thread>
#include <chrono>

#include "gameobject.hpp"
#include "renderer.hpp"


int main()
{
    // initiallization
    Renderer r;
    GameObject wtop(0, 0, 70, 1);
    GameObject wbot(0, 19, 70, 1);
    GameObject wleft(0, 0, 1, 19);
    GameObject wright(68, 0, 1, 19);
        // add walls to render list 
    r.render(&wtop);
    r.render(&wbot);
    // r.render(&wleft);
    // r.render(&wright);

    // Create game objects
    GameObject e1(3, 7, 1, 6);
    GameObject ball(35, 9, 2, 2);
    GameObject e2(65, 7, 1, 6);
        // add entities to render list
    r.render(&e1);
    r.render(&e2);
    r.render(&ball);

    // List of collidable objects to check the ball against
    std::vector<GameObject*> bouncyWalls = { &wtop, &wbot };
    std::vector<GameObject*> pans = { &e1, &e2 };
    std::vector<GameObject*> finishWalls = { &wright, &wleft };

    Vector2D ballSpeed(1, 1);

    // Main loop
    while (true)
    {
        // collision check
        for (GameObject* wall : bouncyWalls)
        {
            if (ball.collision(*wall, ballSpeed))
                ballSpeed.y *= -1;
        }

        for (GameObject* pan : pans)
        {
            if (ball.collision(*pan, ballSpeed))
                ballSpeed.x *= -1;
        }

        for (GameObject* wall : finishWalls)
        {
            if (ball.collision(*wall, ballSpeed))
                ballSpeed.x *= -1;
        }

        // movement update
        ball.move(ballSpeed.x, ballSpeed.y);
        e1.move(0, ballSpeed.y);
        e2.move(0, ballSpeed.y);

        // render
        // std::cout << "\033[2J\033[1;1H" << std::flush;
        r.render();

        std::this_thread::sleep_for(std::chrono::milliseconds(50)); // fps cap to 20
    }
}