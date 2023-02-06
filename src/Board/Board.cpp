//
// Created by Max on 06.02.2023.
//

#include "Board.h"

Board::Board()
{
    boardRec.width = tileSize * boardSize.x + ((boardSize.x - 1) * tileMargins);
    boardRec.height = tileSize * boardSize.y + ((boardSize.y - 1) * tileMargins);
    boardRec.x = GetScreenWidth() / 2 - boardRec.width / 2;
    boardRec.y = GetScreenHeight() / 2 - boardRec.height / 2;


    // Fill board
    // Rows
    for (int i = 0; i < boardSize.y; i++)
    {
        std::vector<Tile> helperVec;
        // Columns
        for (int j = 0; j < boardSize.x; j++)
        {
            Tile tile;
            helperVec.push_back(tile);
        }
        tiles.push_back(helperVec);
    }


}

void Board::Update()
{

}

void Board::Draw()
{
    DrawRectangleRec(boardRec, RED);

    for (int i = 0; i < boardSize.y; i++)
    {

        for (int j = 0; j < boardSize.x; j++)
        {
            DrawRectangle(boardRec.x + j * tileSize + j * tileMargins,
                          (boardRec.y + boardRec.height - tileSize) - i * tileSize - i * tileMargins,
                          tileSize, tileSize, tiles[i][j].color);
        }

    }

}
