//
// Created by 22max on 07.02.2023.
//

#pragma once

#include "Piece.h"

class PieceI : public Piece {

public:
    //PieceI(Vector2 boardDimensions);

    PieceI(Vector2 centerPos);

    int rotate() override;



};
