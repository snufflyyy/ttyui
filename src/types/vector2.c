#include "types/vector2.h"

inline TtyuiVector2 ttyui_vector2_add(TtyuiVector2 a, TtyuiVector2 b) {
    return (TtyuiVector2) { a.x + b.x, a.y + b.y };
}

inline TtyuiVector2 ttyui_vector2_subtract(TtyuiVector2 a, TtyuiVector2 b) {
    return (TtyuiVector2) { a.x - b.x, a.y - b.y };
}
