//
// Created by Max on 24.03.2023.
//

#pragma once

#include "Piece.h"

class PieceL : public Piece {

public:

    PieceL(Vector2 centerPos);

    int rotate() override;

};
