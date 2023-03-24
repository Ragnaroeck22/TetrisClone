//
// Created by 22max on 07.02.2023.
//

#include "PieceI.h"

PieceI::PieceI(Vector2 centerPos)
{
    assignColor();
    this->centerCoords = centerPos;

    blockRelPos.push_back({0, 0});
    blockRelPos.push_back({-1, 0});
    blockRelPos.push_back({1, 0});
    blockRelPos.push_back({2, 0});
}

int PieceI::rotate()
{

    switch (rotation)
    {
        case 0:
            blockRelPos[1].x = 0;
            blockRelPos[1].y = -1;
            blockRelPos[2].x = 0;
            blockRelPos[2].y = 1;
            blockRelPos[3].x = 0;
            blockRelPos[3].y = 2;
            rotation = 1;
            break;
        case 1:
            blockRelPos[1].x = -1;
            blockRelPos[1].y = 0;
            blockRelPos[2].x = 1;
            blockRelPos[2].y = 0;
            blockRelPos[3].x = 2;
            blockRelPos[3].y = 0;
            rotation = 0;
            break;
    }

    return 0;
}
