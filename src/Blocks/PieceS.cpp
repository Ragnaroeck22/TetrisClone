//
// Created by Max on 24.03.2023.
//

#include "PieceS.h"

PieceS::PieceS(Vector2 centerPos)
{
    assignColor();
    this->centerCoords = centerPos;

    blockRelPos.push_back({0, 0});
    blockRelPos.push_back({1, 0});
    blockRelPos.push_back({-1, -1});
    blockRelPos.push_back({0, -1});
}

int PieceS::rotate()
{
    switch (rotation)
    {
        case 0:
            blockRelPos[1].x = -1;
            blockRelPos[1].y = 1;
            blockRelPos[2].x = -1;
            blockRelPos[2].y = 0;
            blockRelPos[3].x = 0;
            blockRelPos[3].y = -1;
            rotation = 1;
            break;
        case 1:
            blockRelPos[1].x = 1;
            blockRelPos[1].y = 0;
            blockRelPos[2].x = -1;
            blockRelPos[2].y = -1;
            blockRelPos[3].x = 0;
            blockRelPos[3].y = -1;
            rotation = 0;
            break;
    }
    return 0;
}
