//
// Created by Max on 06.02.2023.
//

#include "Board.h"

#include <random>

#include "../Blocks/PieceI.h"

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
            Tile tile({static_cast<float>(i) , static_cast<float>(j)});
            helperVec.push_back(tile);
        }
        tiles.push_back(helperVec);
    }

    activePiece = std::make_shared<PieceI>(boardSize);

}

void Board::Update()
{

}

void Board::Draw()
{
    DrawRectangleRec(boardRec, GRAY);

    for (int i = 0; i < boardSize.y; i++)
    {
        for (int j = 0; j < boardSize.x; j++)
        {
            if (tiles[i][j].contents != nullptr)
            {
                DrawRectangle(boardRec.x + j * tileSize + j * tileMargins,
                              (boardRec.y + boardRec.height - tileSize) - i * tileSize - i * tileMargins,
                              tileSize, tileSize, tiles[i][j].contents->color);
            }
            else
            {
                DrawRectangle(boardRec.x + j * tileSize + j * tileMargins,
                              (boardRec.y + boardRec.height - tileSize) - i * tileSize - i * tileMargins,
                              tileSize, tileSize, BLACK);
            }
        }

    }

    // Draw active piece

    // Get tile position

    activePiece->Draw({100, 100}, tileSize, tileMargins);

}

std::shared_ptr<Piece> Board::getPieceFromPool()
{
    if (piecePool.empty())
        genNewPiecePool();

    int random = rand() % piecePool.size();
    std::shared_ptr<Piece> piece = piecePool[random];
    piecePool.erase(piecePool.cbegin() + random);
    return piece;
}

void Board::genNewPiecePool()
{
    piecePool.clear();
    piecePool.push_back(std::make_shared<PieceI>(boardSize));
}

void Board::spawnPiece()
{
    std::shared_ptr<Piece> pieceToSpawn = getPieceFromPool();

    // Spawnpoint coords: 12 | 9 (But remember: tiles[y][x])


}
