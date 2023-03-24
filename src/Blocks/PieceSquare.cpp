//
// Created by Max on 24.03.2023.
//

#include "PieceSquare.h"

PieceSquare::PieceSquare(Vector2 centerPos)
{
    assignColor();
    this->centerCoords = centerPos;

    blockRelPos.push_back({0, 0});
    blockRelPos.push_back({1, 0});
    blockRelPos.push_back({0, -1});
    blockRelPos.push_back({1, -1});
}

int PieceSquare::rotate()
{
    // Nothing :)
    return 0;
}
