//
// Created by 22max on 07.02.2023.
//

#pragma once

#include "raylib.h"
#include <random>

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