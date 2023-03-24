//
// Created by Max on 24.03.2023.
//

#pragma once

#include "Piece.h"

class PieceS : public Piece{

public:

    PieceS(Vector2 centerPos);

    int rotate() override;

};
