#include <iostream>

#include "gameobject.hpp"


int main()
{
    GameObject e(10, 10, 4, 4);

    std::cout << e.stringifyPos() << std::flush;
    std::cout << e.stringify() << std::endl;
}