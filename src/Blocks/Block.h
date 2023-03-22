//
// Created by Max on 22.03.2023.
//

#pragma once

#include "raylib.h"

class Block {

public:
    Color color;
    bool isStatic = false;

    Vector2 coordinates;

    Block(Color color);
};

