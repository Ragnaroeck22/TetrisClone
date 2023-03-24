//
// Created by Max on 24.03.2023.
//

#pragma once

#include "Piece.h"

class PieceSquare : public Piece{

public:

    PieceSquare(Vector2 centerPos);

    int rotate() override;

};


