//
// Created by 22max on 07.02.2023.
//

#pragma once

#include "../Board/Tile.h"

class Piece {

public:

    static const int BLOCKCOUNT = 4;

    Tile blocks[BLOCKCOUNT];

    int rotation = 0;

    Color color;

    virtual int rotate() = 0;
    virtual void assignColor();

    virtual void Draw(Vector2 centerPosition, int tileSize, int tileMargins);

};

