//
// Created by 22max on 07.02.2023.
//

#include "PieceI.h"

PieceI::PieceI(Vector2 centerPos)
{
    this->centerCoords = centerPos;

    blockRelPos.push_back({0, 0});
    blockRelPos.push_back({-1, 0});
    blockRelPos.push_back({1, 0});
    blockRelPos.push_back({2, 0});
}

/*
PieceI::PieceI(Vector2 boardDimensions)
{

    blocks[0].coordinates.x = boardDimensions.x / 2; // Center
    blocks[0].coordinates.y = boardDimensions.y - 1; // Top
    blocks[1].coordinates = {blocks[0].coordinates.x, blocks[0].coordinates.y + 1};
    blocks[2].coordinates = {blocks[0].coordinates.x, blocks[0].coordinates.y - 1};
    blocks[3].coordinates = {blocks[0].coordinates.x, blocks[0].coordinates.y - 2};

    assignColor();

}
*/
int PieceI::rotate()
{



    /*
    switch(rotation)
    {
        case 0:
            blocks[1].coordinates = {blocks[0].coordinates.x - 1, blocks[0].coordinates.y};
            blocks[2].coordinates = {blocks[0].coordinates.x + 1, blocks[0].coordinates.y};
            blocks[3].coordinates = {blocks[0].coordinates.x + 2, blocks[0].coordinates.y};
            return 0;
        case 1:
            blocks[1].coordinates = {blocks[0].coordinates.x, blocks[0].coordinates.y + 1};
            blocks[2].coordinates = {blocks[0].coordinates.x, blocks[0].coordinates.y - 1};
            blocks[3].coordinates = {blocks[0].coordinates.x, blocks[0].coordinates.y - 2};
            return 0;
    }
     */
}

