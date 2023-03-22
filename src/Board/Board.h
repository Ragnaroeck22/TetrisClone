//
// Created by Max on 06.02.2023.
//

#pragma once

#include "raylib.h"
#include <vector>
#include <memory>
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

    std::shared_ptr<Piece> activePiece; // Obsolete?

    std::vector<std::shared_ptr<Piece>> piecePool;

public:
    Board();

    void Update();
    void Draw();


    std::shared_ptr<Piece> getPieceFromPool();


private:
    void genNewPiecePool();

    void spawnPiece();

    void rotatePiece();
};


