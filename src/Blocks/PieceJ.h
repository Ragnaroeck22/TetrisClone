//
// Created by Max on 24.03.2023.
//

#pragma once

#include "Piece.h"

class PieceJ : public Piece{

public:

    PieceJ(Vector2 centerPos);

    int rotate() override;
};
