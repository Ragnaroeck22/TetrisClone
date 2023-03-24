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
    handleMoveTick();

    handlePlayerMovement();

    if (!activePiece->isActive)
    {
        spawnPiece();
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

bool Board::isTileFree(int posX, int posY)
{
    if (posX < 0 || posY < 0 || posY > tiles.size() - 1 || posX > tiles[posY].size() - 1)
    {
        return false;
    }


    if (tiles[posY][posX].contents != nullptr)
    {
        if (tiles[posY][posX].contents->isStatic)
        {
            return false;
        }
    }
    return true;
}

void Board::rotatePiece()
{
    std::vector<Vector2> rotationMemory = activePiece->blockRelPos;

    activePiece->rotate();

    // Check if rotation is possible
    for (int i = 0; i < activePiece->blockRelPos.size(); i++)
    {
        int xToCheck = activePiece->centerCoords.x + activePiece->blockRelPos[i].x;
        int yToCheck = activePiece->centerCoords.y + activePiece->blockRelPos[i].y;

        if (!isTileFree(xToCheck, yToCheck))
        {
            // Rotation failed, revert to previous block positions
            TraceLog(LOG_INFO, "Failed to rotate Piece");
            activePiece->blockRelPos = rotationMemory;
            return;
        }
    }

    // Delete old positions
    for (int i = 0; i < rotationMemory.size(); i++)
    {
        int xToDelete = activePiece->centerCoords.x + rotationMemory[i].x;
        int yToDelete = activePiece->centerCoords.y + rotationMemory[i].y;
        tiles[yToDelete][xToDelete].contents = nullptr;
    }

    // Create new blocks
    for (int i = 0; i < activePiece->blockRelPos.size(); i++)
    {
        int xToCreate = activePiece->centerCoords.x + activePiece->blockRelPos[i].x;
        int yToCreate = activePiece->centerCoords.y + activePiece->blockRelPos[i].y;
        tiles[yToCreate][xToCreate].contents = std::make_shared<Block>(activePiece->color);
    }

}

void Board::movePiece(Direction direction)
{
    bool movePossible = true;
    Vector2 centerMemory = activePiece->centerCoords;

    switch (direction)
    {
        case LEFT:
            // Check if move is possible
            for (int i = 0; i < activePiece->blockRelPos.size(); i++)
            {
                int xToCheck = activePiece->centerCoords.x + activePiece->blockRelPos[i].x - 1;
                int yToCheck = activePiece->centerCoords.y + activePiece->blockRelPos[i].y;

                if (!isTileFree(xToCheck, yToCheck))
                {
                    movePossible = false;
                }
            }
            // Move center
            if (movePossible)
            {
                activePiece->centerCoords.x = activePiece->centerCoords.x - 1;
            }
            break;

        case RIGHT:
            // Check if move is possible
            for (int i = 0; i < activePiece->blockRelPos.size(); i++)
            {
                int xToCheck = activePiece->centerCoords.x + activePiece->blockRelPos[i].x + 1;
                int yToCheck = activePiece->centerCoords.y + activePiece->blockRelPos[i].y;

                if (!isTileFree(xToCheck, yToCheck))
                {
                    movePossible = false;
                }
            }
            // Move center
            if (movePossible)
            {
                activePiece->centerCoords.x = activePiece->centerCoords.x + 1;
            }
            break;

        case DOWN:
            // Check if move is possible
            for (int i = 0; i < activePiece->blockRelPos.size(); i++)
            {
                int xToCheck = activePiece->centerCoords.x + activePiece->blockRelPos[i].x;
                int yToCheck = activePiece->centerCoords.y + activePiece->blockRelPos[i].y - 1;

                if (!isTileFree(xToCheck, yToCheck))
                {
                    movePossible = false;
                }
            }
            // Move center
            if (movePossible)
            {
                activePiece->centerCoords.y = activePiece->centerCoords.y - 1;
            }

            break;

        default:
            return;
    }

    // Move blocks
    if (movePossible)
    {

        // Delete old positions
        for (int i = 0; i < activePiece->blockRelPos.size(); i++)
        {
            int xToDelete = centerMemory.x + activePiece->blockRelPos[i].x;
            int yToDelete = centerMemory.y + activePiece->blockRelPos[i].y;
            tiles[yToDelete][xToDelete].contents = nullptr;
        }

        // Create new blocks
        for (int i = 0; i < activePiece->blockRelPos.size(); i++)
        {
            int xToCreate = activePiece->centerCoords.x + activePiece->blockRelPos[i].x;
            int yToCreate = activePiece->centerCoords.y + activePiece->blockRelPos[i].y;
            tiles[yToCreate][xToCreate].contents = std::make_shared<Block>(activePiece->color);
        }
    }

    // Make piece static if it cant move down
    if (direction == DOWN)
    {
        bool disablePiece = false;
        for (int i = 0; i < activePiece->blockRelPos.size(); i++)
        {
            int xToCheck = activePiece->centerCoords.x + activePiece->blockRelPos[i].x;
            int yToCheck = activePiece->centerCoords.y + activePiece->blockRelPos[i].y - 1;

            if (!isTileFree(xToCheck, yToCheck))
            {
                disablePiece = true;
            }
        }
        if (disablePiece)
        {
            activePiece->isActive = false;
            for (int i = 0; i < activePiece->blockRelPos.size(); i++)
            {
                int targetX = activePiece->centerCoords.x + activePiece->blockRelPos[i].x;
                int targetY = activePiece->centerCoords.y + activePiece->blockRelPos[i].y;

                if (tiles[targetY][targetX].contents != nullptr) // Just in case
                {
                    tiles[targetY][targetX].contents->isStatic = true;
                }
            }
        }
    }

}

void Board::handleMoveTick()
{
    moveTickTimer++;

    if (moveTickTimer >= moveTickTarget * moveTickModifier)
    {
        moveTickTimer = 0;
        if (!IsKeyDown(KEY_DOWN)) // Disable move tick when manually moving a piece downwards
        {
            movePiece(DOWN);
        }
    }
}

void Board::handlePlayerMovement()
{
    if (IsKeyPressed(KEY_UP))
    {
        rotatePiece();
    }

    if(IsKeyPressed(KEY_LEFT) || IsKeyPressed(KEY_RIGHT) || IsKeyPressed(KEY_DOWN))
    {
        playerMoveTickTimer = playerMoveTickTarget;
    }

    if (IsKeyDown(KEY_LEFT) && playerMoveTickTimer >= playerMoveTickTarget)
    {
        movePiece(LEFT);
        playerMoveTickTimer = 0;
    }
    if (IsKeyDown(KEY_RIGHT) && playerMoveTickTimer >= playerMoveTickTarget)
    {
        movePiece(RIGHT);
        playerMoveTickTimer = 0;
    }

    if (IsKeyDown(KEY_DOWN) && playerMoveTickTimer >= playerMoveTickTarget)
    {
        movePiece(DOWN);
        playerMoveTickTimer = 0;
    }

    if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_DOWN))
    {
        playerMoveTickTimer++;
    }
}

