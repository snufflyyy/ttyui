#pragma once

typedef struct Vector2 {
    int x, y;
} Vector2;

Vector2 ttyui_vector2_add(Vector2 a, Vector2 b);
Vector2 ttyui_vector2_subtract(Vector2 a, Vector2 b);
