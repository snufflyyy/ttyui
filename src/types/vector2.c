#include "types/vector2.h"

inline Vector2 ttyui_vector2_add(Vector2 a, Vector2 b) {
    return (Vector2) { a.x + b.x, a.y + b.y };
}

inline Vector2 ttyui_vector2_subtract(Vector2 a, Vector2 b) {
    return (Vector2) { a.x - b.x, a.y - b.y };
}
