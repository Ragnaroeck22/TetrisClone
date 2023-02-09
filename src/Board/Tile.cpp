//
// Created by 22max on 09.02.2023.
//

#include "Tile.h"

Tile::Tile(Vector2 coordinates, Color color)
{
    this->coordinates = coordinates;
    this->color = color;
}

Tile::Tile(Vector2 coordinates)
{
    this->coordinates = coordinates;
    color = colorDefault;
}

Tile::Tile()
{
    color = colorDefault;
}
