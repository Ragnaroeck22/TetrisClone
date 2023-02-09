//
// Created by 22max on 07.02.2023.
//

#include "Piece.h"

#include "../Other/Functions.h"

void Piece::assignColor()
{
    color = randomColor();

    for (auto & block : blocks)
    {
        block.color = color;
    }
}

void Piece::Draw(Vector2 centerPosition, int tileSize, int tileMargins)
{
    for (auto & block : blocks)
    {
        DrawRectangle(centerPosition.x + (block.coordinates.x * tileSize) + (block.coordinates.x * tileMargins),
                      centerPosition.y + (block.coordinates.y * tileSize) + (block.coordinates.y * tileMargins),
                      tileSize, tileSize, color);

    }
}
