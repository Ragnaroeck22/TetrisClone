//
// Created by Max on 24.03.2023.
//

#pragma once

#include "Piece.h"

class PieceZ : public Piece {

public:

    PieceZ(Vector2 centerPos);

    int rotate() override;

};
