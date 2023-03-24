//
// Created by Max on 06.02.2023.
//

#include "Board.h"

#include <random>
#include <cmath>

#include "../Blocks/PieceI.h"
#include "../Blocks/PieceT.h"
#include "../Blocks/PieceS.h"
#include "../Blocks/PieceZ.h"
#include "../Blocks/PieceL.h"
#include "../Blocks/PieceJ.h"
#include "../Blocks/PieceSquare.h"
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

    displayBoardRec.width = tileSize * displayBoardSize + ((displayBoardSize - 1) * tileMargins);
    displayBoardRec.height = displayBoardRec.width;
    displayBoardRec.x = boardRec.x + boardRec.width + (GetScreenWidth() * 0.05);
    displayBoardRec.y = boardRec.y;


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

    for (int i = 0; i < displayBoardSize; i++)
    {
        TraceLog(LOG_INFO, "Building db");
        std::vector<Tile> helperVec;
        // Columns
        for (int j = 0; j < displayBoardSize; j++)
        {
            Tile tile({static_cast<float>(i) , static_cast<float>(j)});
            helperVec.push_back(tile);
        }
        displayBoard.push_back(helperVec);
    }
    spawnPiece();
    updateDisplayBoard();

}

void Board::Update()
{
    handlePlayerMovement();

    handleMoveTick();

    if (!activePiece->isActive)
    {
        dropBlocks();
        spawnPiece();
        updateDisplayBoard();
    }

}

void Board::Draw()
{
    // Draw board
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

    // Draw display board
    DrawRectangleRec(displayBoardRec, GRAY);

    for (int i = 0; i < displayBoardSize; i++)
    {
        for (int j = 0; j < displayBoardSize; j++)
        {
            if (displayBoard[i][j].contents != nullptr)
            {
                DrawRectangle(displayBoardRec.x + j * tileSize + j * tileMargins,
                              (displayBoardRec.y + displayBoardRec.height - tileSize) - i * tileSize - i * tileMargins,
                              tileSize, tileSize, displayBoard[i][j].contents->color);
            }
            else
            {
                DrawRectangle(displayBoardRec.x + j * tileSize + j * tileMargins,
                              (displayBoardRec.y + displayBoardRec.height - tileSize) - i * tileSize - i * tileMargins,
                              tileSize, tileSize, BLACK);
            }
        }

    }

    std::string scoreMsg = "Score: ";
    scoreMsg.append(std::to_string(score));
    DrawText(scoreMsg.c_str(),
             displayBoardRec.x, displayBoardRec.y + displayBoardRec.height + (GetScreenHeight() * 0.05),
             fontSize, BLACK);

    int targetY = displayBoardRec.y + displayBoardRec.height + (GetScreenHeight() * 0.1) + fontSize;
    std::string lineMsg = "Lines Cleared: ";
    lineMsg.append(std::to_string(linesCleared));
    DrawText(lineMsg.c_str(),
             displayBoardRec.x,
             targetY,
             fontSize, BLACK);

    std::string modifierMsg = "Move Tick Modifier: ";
    int modifier = moveTickModifier * 100;
    modifierMsg.append(std::to_string(modifier));
    DrawText(modifierMsg.c_str(),
             displayBoardRec.x,
             targetY + (GetScreenHeight() * 0.05) + fontSize,
             fontSize, BLACK);

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

std::shared_ptr<Piece> Board::getPieceFromBuffer()
{
    if (pieceBuffer == nullptr) // Handles buffer initialisation
    {
        pieceBuffer = getPieceFromPool();
    }

    std::shared_ptr<Piece> returnPiece = pieceBuffer;
    pieceBuffer = getPieceFromPool();
    return returnPiece;
}


void Board::genNewPiecePool()
{
    piecePool.clear();

    piecePool.push_back(std::make_shared<PieceI>(spawnPosition));
    piecePool.push_back(std::make_shared<PieceT>(spawnPosition));
    piecePool.push_back(std::make_shared<PieceS>(spawnPosition));
    piecePool.push_back(std::make_shared<PieceZ>(spawnPosition));
    piecePool.push_back(std::make_shared<PieceL>(spawnPosition));
    piecePool.push_back(std::make_shared<PieceJ>(spawnPosition));
    piecePool.push_back(std::make_shared<PieceSquare>(spawnPosition));
}

void Board::spawnPiece()
{

    activePiece = getPieceFromBuffer();

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
    bool disablePiece = false;

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
                    disablePiece = true;
                }
            }
            // Move center
            if (movePossible) {
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

void Board::dropBlocks()
{
    bool lineHasBeenDropped;
    int linesDroppedLocal = 0;

    do
    {
        lineHasBeenDropped = false;

        // Look for lines to delete
        for (int i = 0; i < tiles.size(); i++) {
            bool fullLine = true;
            for (int j = 0; j < tiles[i].size(); j++) {
                if (isTileFree(j, i)) {
                    fullLine = false;
                }
            }

            if (fullLine) {
                tiles.erase(tiles.cbegin() + i);
                std::vector<Tile> newX;
                for (int j = 0; j < boardSize.x; j++) {
                    Tile newTile({static_cast<float>(j), boardSize.y});
                    newX.push_back(newTile);
                }
                tiles.push_back(newX);

                // Re-assign coordinates
                for (int j = 0; j < tiles.size(); j++) {
                    for (int k = 0; k < tiles[j].size(); k++) {
                        tiles[j][k].coordinates.x = k;
                        tiles[j][k].coordinates.y = j;
                    }
                }
                lineHasBeenDropped = true;
                linesDroppedLocal++;
                linesCleared++;
                updateMoveTickModifier();
            }
        }
    } while (lineHasBeenDropped);

    switch (linesDroppedLocal)
    {
        case 1:
            score += 100;
            break;
        case 2:
            score += 300;
            break;
        case 3:
            score += 600;
            break;
        case 4:
            score += 1000;
    }
}

void Board::updateDisplayBoard()
{
    // Clear display board
    for (int i = 0; i < displayBoard.size(); i++)
    {
        for (int j = 0; j < displayBoard[i].size(); j++)
        {
            displayBoard[i][j].contents = nullptr;
        }
    }
    // Load buffer piece into display board
    int targetCenter = displayBoardSize / 2;
    for (int i = 0; i < pieceBuffer->blockRelPos.size(); i++)
    {
        int targetX = targetCenter + pieceBuffer->blockRelPos[i].x;
        int targetY = targetCenter + pieceBuffer->blockRelPos[i].y;

        displayBoard[targetY][targetX].contents = std::make_shared<Block>(pieceBuffer->color);
    }
}

void Board::updateMoveTickModifier()
{
    moveTickModifier = pow(1.1, -linesCleared);
}
