#pragma once

#include <cmath>
#include <list>
#include <vector>


/**
 * @brief Store and manipulate with x and y coordinates 
 * 
 */
struct Vector2D
{
    int x, y;

    Vector2D() : x(0), y(0) { }
    Vector2D(const int &a_x, const int &a_y) : x(a_x), y(a_y) { }

    /**
     * @brief Add two Vector2D together
     * 
     * @param other - new Vector2D object
     * @return new Vector2D
     */
    Vector2D operator+(const Vector2D &other) const
    {
        int new_x = x + other.x; 
        int new_y = y + other.y;

        return Vector2D(new_x, new_y);
    }

    /**
     * @brief Subtract second Vector2D from the original(first)
     * 
     * @param other - new Vector2D object
     * @return new Vector2D
     */
    Vector2D operator-(const Vector2D &other) const
    {
        int new_x = x - other.x; 
        int new_y = y - other.y;

        return Vector2D(new_x, new_y);
    }

    /**
     * @brief Add two Vector2D together, inplace
     * 
     * @param other - reference to the other Vector2D
     */
    Vector2D operator+=(const Vector2D &other)
    {
        x += other.x; y += other.y;

        return *this;
    }

    /**
     * @brief Subtract second Vector2D from the original(first)
     * 
     * @param other - reference to the other Vector2D
     */
    Vector2D operator-=(const Vector2D &other)
    {
        x -= other.x; y -= other.y;

        return *this;
    }

    /**
     * @brief Get the distance of two Vector2D objs
     * 
     * @param other reference to the other Vector2D 
     * @return int 
     */
    int distance(const Vector2D& other) const
    {
        int new_x = std::abs(x - other.x);
        int new_y = std::abs(y - other.y);

        return std::sqrt(std::pow(new_x, 2) + std::pow(new_y, 2));
    }

    /**
     * @brief Multiple of the vector's x and y
     * 
     * @return int 
     */
    int value() const
    {
        return x * y;
    }
};

/**
 * @brief Stores position and size of the object, functions for easier manipulation
 * 
 */
struct GameObject 
{
    Vector2D position; // position of game object in world view
    Vector2D size; // size of game object

    // Construct new Game object with initial values
    GameObject(const int &x, const int &y, const unsigned int &width, const unsigned int &height)
        : position(x, y), size(width, height) { } 
    // Construct new Game object with initial values
    GameObject(const unsigned int &width, const unsigned int &height)
        : position(), size(width, height) { }
    // Construct new empty Game object
    GameObject() 
        : position(), size(1, 1) { } 

    /**
     * @brief Will this GameObject with its actuall speed collide with the given GameObject
     * 
     * @param other - Reference to the other game object
     * @param speed - speed of this game object
     * @return bool
     */
    bool collision(const GameObject& other, const Vector2D& speed) const
    {
        int x_check = position.x + !std::signbit(speed.x) * size.x;
        int y_check = position.y + !std::signbit(speed.y) * size.y;

        if (x_check >= other.position.x && x_check <= other.position.x + other.size.x)
            if (y_check >= other.position.y && y_check <= other.position.y + other.size.y)
                return true;

        return false;
    }

    // add given values to the object's position
    void move(const int& x, const int& y)
    {
        position += Vector2D(x, y);
    }

    // add given vector to the object's position
    void move(const Vector2D& speed)
    {
        position += speed;
    }

    // move object to given x and y
    void moveTo(const int& x, const int& y)
    {
        position.x = x; position.y = y;
    }

    // move object to give Vector2D position
    void moveTo(const Vector2D new_pos)
    {
        position = new_pos;
    }

    // Array of all coordinates occupuied by this object
    void toArray(std::vector<Vector2D> *out) const
    {
        out->reserve(size.value());

        for (int y = 0; y < size.y; y++)
        {
            for (int x = 0; x < size.x; x++)
                out->push_back(Vector2D(position.x + x, position.y + y));
        }
    }
};