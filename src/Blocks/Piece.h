//
// Created by 22max on 07.02.2023.
//

#pragma once

#include "../Board/Tile.h"
#include <vector>

class Piece {

public:

    static const int BLOCKCOUNT = 4;

    std::vector<Vector2> blockRelPos;

    int rotation = 0;

    Color color;

    Vector2 centerCoords;
    bool isActive = true;

    virtual int rotate() = 0;
    virtual void assignColor();

    virtual void Draw(Vector2 centerPosition, int tileSize, int tileMargins);

};

