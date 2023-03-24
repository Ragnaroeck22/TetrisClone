//
// Created by Max on 22.03.2023.
//

#include "Functions.h"

Color randomColor()
    {
        int random;
        random = rand() % 10;

        switch (random)
        {
            case 0:
                return RED;
            case 1:
                return GREEN;
            case 2:
                return BLUE;
            case 3:
                return YELLOW;
            case 4:
                return ORANGE;
            case 5:
                return PINK;
            case 6:
                return MAROON;
            case 7:
                return LIME;
            case 8:
                return DARKBLUE;
            case 9:
                return DARKGREEN;
            case 10:
                return SKYBLUE;
            case 11:
                return PURPLE;
            case 12:
                return VIOLET;
            case 13:
                return DARKPURPLE;
            default:
                return RED;
        }
}

std::vector<Vector2> vecLowestX(std::vector<Vector2> vecToCheck)
{
    if (vecToCheck.size() > 0)
    {
        float memory = vecToCheck[0].x;

        // Set up memory
        for (int i = 0; i < vecToCheck.size(); i++)
        {
            if (vecToCheck[i].x < memory)
            {
                memory = vecToCheck[i].x;
            }
        }
        // Fill return vector
        std::vector<Vector2> returnVec;
        for (int i = 0; i < vecToCheck.size(); i++)
        {
            if (vecToCheck[i].x == memory)
                returnVec.push_back(vecToCheck[i]);
        }
        return returnVec;
    }
    else
        return vecToCheck;
}

std::vector<Vector2> vecHighestX(std::vector<Vector2> vecToCheck)
{
    if (vecToCheck.size() > 0)
    {
        float memory = vecToCheck[0].x;

        // Set up memory
        for (int i = 0; i < vecToCheck.size(); i++)
        {
            if (vecToCheck[i].x > memory)
            {
                memory = vecToCheck[i].x;
            }
        }
        // Fill return vector
        std::vector<Vector2> returnVec;
        for (int i = 0; i < vecToCheck.size(); i++)
        {
            if (vecToCheck[i].x == memory)
                returnVec.push_back(vecToCheck[i]);
        }
        return returnVec;
    }
    else
        return vecToCheck;
}

std::vector<Vector2> vecLowestY(std::vector<Vector2> vecToCheck)
{
    if (vecToCheck.size() > 0)
    {
        float memory = vecToCheck[0].y;

        // Set up memory
        for (int i = 0; i < vecToCheck.size(); i++)
        {
            if (vecToCheck[i].y > memory)
            {
                memory = vecToCheck[i].y;
            }
        }
        // Fill return vector
        std::vector<Vector2> returnVec;
        for (int i = 0; i < vecToCheck.size(); i++)
        {
            if (vecToCheck[i].y == memory)
                returnVec.push_back(vecToCheck[i]);
        }
        return returnVec;
    }
    else
        return vecToCheck;
}
