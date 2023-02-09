//
// Created by 22max on 09.02.2023.
//

#pragma once

#include "raylib.h"

class Tile {

public:
    Vector2 coordinates;
    bool isBlocked = false;
    Color color;

private:
    Color colorDefault = BLACK;

public:
    Tile(Vector2 coordinates, Color color);
    Tile(Vector2 coordinates);
    Tile(); // Fuck this
};

