//
// Created by Max on 24.03.2023.
//

#pragma once

#include "Piece.h"

class PieceT : public Piece {

public:

    PieceT(Vector2 centerPos);

    int rotate() override;


};

