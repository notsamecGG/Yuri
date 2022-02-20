#pragma once
#include <iostream>
#include <string>
#include <vector>

#include "gameobject.hpp"


struct Renderer
{
    Renderer ()
        : charNum(0), objs() { }

    void render() 
    { 
        if (objs.size() == 0)
            return;
        
        for (GameObject obj : objs)
        {
            std::cout << obj.stringify() << std::endl;
        }
    }

    void render(std::string& input)
    {
        buffer = input;
        charNum = input.size();

        render();
    }
    
    void clear()
    {
        std::string clearStr("");
        buffer.clear();

        while(charNum)
        {
            clearStr += "\b";
            charNum--;
        }

        std::cout << clearStr << std::flush;
    }

private:
    unsigned int charNum; // count of all chars in fram (formated)
    std::vector<GameObject> objs;
};