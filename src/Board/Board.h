//
// Created by Max on 06.02.2023.
//

#pragma once

#include "raylib.h"
#include <vector>
#include <memory>
#include "../Other/Enums.h"
#include "Tile.h"
#include "../Blocks/Piece.h"

class Board {

public:
    Rectangle boardRec;
    int tileMargins = 1;
    int tileSize = 40;
    Vector2 boardSize = {10, 24};
    Vector2 spawnPosition;

    std::vector<std::vector<Tile>> tiles; // When accessing single tiles: [y][x] (this pains me, but it's better this way)

    std::shared_ptr<Piece> activePiece;

    std::vector<std::shared_ptr<Piece>> piecePool;

    // Move tick stuff
    int moveTickTimer = 0;
    int moveTickTarget = 90;
    float moveTickModifier = 1;
    // Player movement
    int playerMoveTickTimer = 0;
    int playerMoveTickTarget = 6;


public:
    Board();

    void Update();
    void Draw();


    std::shared_ptr<Piece> getPieceFromPool();


private:
    void genNewPiecePool();

    void spawnPiece();
    bool isTileFree(int posX, int posY); // Check if a tile is free

    void rotatePiece();
    void movePiece(Direction direction);

    void handleMoveTick();
    void handlePlayerMovement();

    void dropBlocks();
};


