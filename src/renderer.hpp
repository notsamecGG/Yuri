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
        
        std::vector<Vector2D> objBuffer;
        objBuffer.reserve(sizeSum());

        // Vector2D objBuffer[sizeSum()];

        int index = 0;
        for (GameObject obj : objs)
        {
            obj.toArray(objBuffer.data(), index);
            index += obj.size.value();
        }

        std::vector<int> posBuffer;
        bufferToDisplay(objBuffer, &posBuffer);

        std::string display(DISPLAY_X * DISPLAY_Y, ' ');
        // char display[DISPLAY_X * DISPLAY_Y];
        for (int y = 0; y < DISPLAY_Y; y++)
        {
            for (int x = 0; x < DISPLAY_X; x++)
            {
                if(posBuffer.end() == std::find(posBuffer.begin(), posBuffer.end(), x + y * DISPLAY_X))
                    display[x + y * DISPLAY_X] = '#';
                // else
                    // display[x + y * DISPLAY_X] = ' ';
            }

            display[DISPLAY_X - 1 + y * DISPLAY_X] = '\n';
        }

        std::cout << display << std::flush;
    }

    void render(GameObject& go)
    {
        objs.push_back(go);
        // charNum = input.size();

        render();
    }
    
    // void clear()
    // {
    //     std::string clearStr("");
    //     buffer.clear();

    //     while(charNum)
    //     {
    //         clearStr += "\b";
    //         charNum--;
    //     }

    //     std::cout << clearStr << std::flush;
    // }

private:
    int sizeSum()
    {
        int size = 0;

        for (GameObject obj : objs)
            size += obj.size.value();

        return size;
    }

    void bufferToDisplay(std::vector<Vector2D>& objBuffer, std::vector<int>* out)
    {
        out->reserve(objBuffer.size());

        int index = 0;
        for (Vector2D vec : objBuffer)
        {
            (*out)[index] = vec.x + vec.y * DISPLAY_X;
            index++;
        }
    } 

private:
    unsigned int charNum; // count of all chars in fram (formated)
    std::vector<GameObject> objs;
};