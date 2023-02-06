//
// Created by Max on 06.02.2023.
//

#pragma once

#include "raylib.h"
#include <vector>
#include "Tile.h"

class Board {

public:
    Rectangle boardRec;
    int tileMargins = 1;
    int tileSize = 40;
    Vector2 boardSize = {10, 24};

    std::vector<std::vector<Tile>> tiles; // When accessing single tiles: [y][x] (this pains me, but it's better this way)


public:
    Board();

    void Update();
    void Draw();


};


