//
// Created by 22max on 07.02.2023.
//

#pragma once

#include "raylib.h"
#include <random>

Color randomColor();

std::vector<Vector2> vecLowestX(std::vector<Vector2> vecToCheck);
std::vector<Vector2> vecHighestX(std::vector<Vector2> vecToCheck);
std::vector<Vector2> vecLowestY(std::vector<Vector2> vecToCheck);