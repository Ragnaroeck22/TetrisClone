//
// Created by Max on 24.03.2023.
//

#include "PieceT.h"

PieceT::PieceT(Vector2 centerPos)
{
    assignColor();
    this->centerCoords = centerPos;

    blockRelPos.push_back({0, 0});
    blockRelPos.push_back({-1, 0});
    blockRelPos.push_back({1, 0});
    blockRelPos.push_back({0, -1});
}

int PieceT::rotate()
{
    switch (rotation)
    {
        case 0:
            blockRelPos[1].x = 0;
            blockRelPos[1].y = 1;
            blockRelPos[2].x = 0;
            blockRelPos[2].y = -1;
            blockRelPos[3].x = -1;
            blockRelPos[3].y = 0;
            rotation = 1;
            break;
        case 1:
            blockRelPos[1].x = 1;
            blockRelPos[1].y = 0;
            blockRelPos[2].x = -1;
            blockRelPos[2].y = 0;
            blockRelPos[3].x = 0;
            blockRelPos[3].y = 1;
            rotation = 2;
            break;
        case 2:
            blockRelPos[1].x = 0;
            blockRelPos[1].y = -1;
            blockRelPos[2].x = 0;
            blockRelPos[2].y = 1;
            blockRelPos[3].x = 1;
            blockRelPos[3].y = 0;
            rotation = 3;
            break;
        case 3:
            blockRelPos[1].x = -1;
            blockRelPos[1].y = 0;
            blockRelPos[2].x = 1;
            blockRelPos[2].y = 0;
            blockRelPos[3].x = 0;
            blockRelPos[3].y = -1;
            rotation = 0;
            break;
    }
    return 0;
}
