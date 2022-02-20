#pragma once
#include <algorithm>
#include <array>
#include <iostream>
#include <string>
#include <vector>

#include "gameobject.hpp"

#define DISPLAY_X 70
#define DISPLAY_Y 20


struct Renderer
{
    Renderer ()
        : charNum(0), objs() { }

    // WARNING: objs are rendered from left to right, so be consious of that 
    // TODO: repair this warning
    void render() 
    { 
        if (objs.size() == 0)
            return;
        
        std::vector<int> posBuffer;
        const int objsSize = sizeSum();
        posBuffer.reserve(objsSize);

        for (GameObject* obj : objs)
        {
            std::vector<Vector2D> objPositions;
            obj->toArray(&objPositions);

            for (Vector2D vec : objPositions)
                posBuffer.push_back(vec.x + vec.y * DISPLAY_X);
        }

        std::string display(DISPLAY_X * DISPLAY_Y, ' ');
        for (int y = 0; y < DISPLAY_Y; y++)
        {
            for (int x = 0; x < DISPLAY_X; x++)
            {
                if(posBuffer.end() != std::find(posBuffer.begin(), posBuffer.end(), x + y * DISPLAY_X))
                    display[x + y * DISPLAY_X] = '#';
            }

            display[DISPLAY_X - 1 + y * DISPLAY_X] = '\n';
        }

        std::cout << display << std::flush;
    }

    void render(GameObject* go)
    {
        objs.push_back(go);
        // charNum = input.size();
    }
    
    void clear()
    {
        // std::string clearStr("");
        // buffer.clear();

        // while(charNum)
        // {
        //     clearStr += "\b";
        //     charNum--;
        // }

        std::string clearStr("");

        for (int i = 0; i < (DISPLAY_X - 10) * (DISPLAY_Y - 10); i++)
        {
            clearStr += "\b ";
        }

        std::cout << clearStr << std::flush;
        // std::cout << "clear" << std::endl;
    }

private:
    int sizeSum()
    {
        int size = 0;

        for (GameObject* obj : objs)
            size += obj->size.value();

        return size;
    }

private:
    unsigned int charNum; // count of all chars in fram (formated)
    std::vector<GameObject*> objs;
};