#include <iostream>

#include "gameobject.hpp"
#include "renderer.hpp"


int main()
{
    GameObject e(10, 10, 4, 4);
    Renderer r;
    
    r.render(e);
}