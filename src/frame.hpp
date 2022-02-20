#pragma once
#include <iostream>
#include <string>
#include <vector>


struct Frame
{
    Frame ()
     : charNum(0), buffer("") { }

    void render() { std::cout << buffer << std::flush; }
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
    std::string buffer; // (unformated) content buffer
};