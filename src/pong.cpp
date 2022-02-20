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
    r.render(&wleft);
    r.render(&wright);


    GameObject e1(10, 5, 4, 4);
    GameObject e2(1, 1, 5, 2);
    
    r.render(&e1);
    r.render(&e2);

    for (int i = 0; i < 100; i++)
    {
        // make this actually remove the text
        std::cout << "\033[2J\033[1;1H" << std::flush;
        // std::cout << "\x1B[3J\x1B[H" << std::flush;
        e2.move(1, 0);
        r.render();

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    // std::cout << "\033[2J\033[1;1H" << std::flush;
}