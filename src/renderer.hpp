#pragma once
#include <algorithm>
#include <array>
#include <iostream>
#include <string>
#include <vector>

#include "gameobject.hpp"

#define DISPLAY_X 70
#define DISPLAY_Y 20


/**
 * @brief Render object serves for managing GameObjects and their render, there should be only one in the whole build
 * 
 */
struct Renderer
{
    /**
     * @brief Construct a new empty Renderer object
     * 
     */
    Renderer ()
        : objs() { }

    // WARNING: objs are rendered from left to right, so be consious of that 
    // TODO: repair this warning

    /**
     * @brief Render list of gameobjects (use render(GameObject go) to add go to list)
     * 
     */
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

        std::cout << "\033[2J\033[1;1H" << std::flush;
        std::cout << display << std::flush;
    }

    /**
     * @brief Add game object to render list
     * 
     * @param go 
     */
    void render(GameObject* go)
    {
        objs.push_back(go);
    }

private:
    // sum all of the objects' dimensions in GO list 
    int sizeSum()
    {
        int size = 0;

        for (GameObject* obj : objs)
            size += obj->size.value();

        return size;
    }

private:
    std::vector<GameObject*> objs; // list of game objects
};