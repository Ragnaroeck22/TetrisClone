//
// Created by 22max on 09.02.2023.
//

#pragma once

#include "raylib.h"
#include <memory>

#include "../Blocks/Block.h"

class Tile {

public:
    std::shared_ptr<Block> contents = nullptr;

    Vector2 coordinates;

private:

public:
    Tile(Vector2 coordinates, Color color);
    Tile(Vector2 coordinates);
    Tile(); // Fuck this
};

