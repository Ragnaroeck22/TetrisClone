//
// Created by Max on 06.02.2023.
//

#include "Board.h"

#include <random>

#include "../Blocks/PieceI.h"
#include "../Other/Functions.h"

Board::Board()
{
    boardRec.width = tileSize * boardSize.x + ((boardSize.x - 1) * tileMargins);
    boardRec.height = tileSize * boardSize.y + ((boardSize.y - 1) * tileMargins);
    boardRec.x = GetScreenWidth() / 2 - boardRec.width / 2;
    boardRec.y = GetScreenHeight() / 2 - boardRec.height / 2;

    int targetX = boardSize.x / 2 - 1;
    int targetY = boardSize.y - 3;
    spawnPosition = {static_cast<float>(targetX), static_cast<float>(targetY)};

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

    spawnPiece();

}

void Board::Update()
{

    if (IsKeyPressed(KEY_UP))
    {
        rotatePiece();
    }

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

    //activePiece->Draw({100, 100}, tileSize, tileMargins);

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

    piecePool.push_back(std::make_shared<PieceI>(spawnPosition));
}

void Board::spawnPiece()
{

    activePiece = getPieceFromPool();

    // TODO: Check win condition here
    //
    //

    for (int i = 0; i < activePiece->blockRelPos.size(); i++)
    {
        tiles[spawnPosition.y + activePiece->blockRelPos[i].y][spawnPosition.x + activePiece->blockRelPos[i].x].contents =
                std::make_shared<Block>(activePiece->color);
    }

}

void Board::rotatePiece()
{
    TraceLog(LOG_INFO, "Rotating");
    std::vector<Vector2> rotationMemory = activePiece->blockRelPos;

    activePiece->rotate();

    // Check if rotation is possible
    TraceLog(LOG_INFO, "Checking if rotation is possible");
    for (int i = 0; i < activePiece->blockRelPos.size(); i++)
    {
        int xToCheck = activePiece->centerCoords.x + activePiece->blockRelPos[i].x;
        int yToCheck = activePiece->centerCoords.y + activePiece->blockRelPos[i].y;

        if (tiles[yToCheck][xToCheck].contents != nullptr)
        {
            if (tiles[yToCheck][xToCheck].contents->isStatic)
            {
                // Rotation failed, revert to previous block positions
                TraceLog(LOG_INFO, "Failed to rotate Piece");
                activePiece->blockRelPos = rotationMemory;
                return;
            }
        }
    }

    // Delete old positions
    TraceLog(LOG_INFO, "Deleting old blocks");
    for (int i = 0; i < rotationMemory.size(); i++)
    {
        int xToDelete = activePiece->centerCoords.x + rotationMemory[i].x;
        int yToDelete = activePiece->centerCoords.y + rotationMemory[i].y;
        tiles[yToDelete][xToDelete].contents = nullptr;
    }

    // Create new blocks
    TraceLog(LOG_INFO, "Creating new blocks");
    for (int i = 0; i < activePiece->blockRelPos.size(); i++)
    {
        int xToDelete = activePiece->centerCoords.x + activePiece->blockRelPos[i].x;
        int yToDelete = activePiece->centerCoords.y + activePiece->blockRelPos[i].y;
        tiles[yToDelete][xToDelete].contents = std::make_shared<Block>(activePiece->color);
    }

}
