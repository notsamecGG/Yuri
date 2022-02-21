#include <iostream>
#include <thread>
#include <chrono>

#include "gameobject.hpp"
#include "renderer.hpp"


int main()
{
    Renderer r;
    GameObject wtop(0, 0, 70, 1);
    GameObject wbot(0, 19, 70, 1);
    GameObject wleft(0, 0, 1, 19);
    GameObject wright(68, 0, 1, 19);
    r.render(&wtop);
    r.render(&wbot);
    // r.render(&wleft);
    // r.render(&wright);


    GameObject e1(3, 1, 1, 5);
    GameObject ball(35, 10, 2, 2);
    GameObject e2(65, 1, 1, 5);
    
    r.render(&e1);
    r.render(&e2);
    r.render(&ball);

    std::vector<GameObject*> bouncyWalls = { &wtop, &wbot };
    std::vector<GameObject*> finishWalls = { &wright, &wleft };

    Vector2D ballSpeed(1, 1);

    while (true)
    {
        // for (int i = 0; i < 13; i++)
        // {
        //     // make this actually remove the text
        //     std::cout << "\033[2J\033[1;1H" << std::flush;
        //     // std::cout << "\x1B[3J\x1B[H" << std::flush;
        //     e1.move(0, x);
        //     e2.move(0, x);
        //     r.render();

        //     std::this_thread::sleep_for(std::chrono::milliseconds(100));
        // }

        // collision check
        for (GameObject* wall : bouncyWalls)
        {
            if (ball.collision(*wall, ballSpeed))
                ballSpeed.y *= -1;
        }

        for (GameObject* wall : finishWalls)
        {
            if (ball.collision(*wall, ballSpeed))
                ballSpeed.x *= -1;
        }

        // movement update
        ball.move(ballSpeed.x, ballSpeed.y);

        // render
        // std::cout << "\033[2J\033[1;1H" << std::flush;
        r.render();

        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
    // std::cout << "\033[2J\033[1;1H" << std::flush;
}