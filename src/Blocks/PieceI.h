//
// Created by 22max on 07.02.2023.
//

#pragma once

#include "Piece.h"

class PieceI : public Piece {

public:
    PieceI(Vector2 boardDimensions);
    int rotate() override;


};
