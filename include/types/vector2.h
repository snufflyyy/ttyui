#pragma once

typedef struct TtyuiVector2 {
    int x, y;
} TtyuiVector2;

TtyuiVector2 ttyui_vector2_add(TtyuiVector2 a, TtyuiVector2 b);
TtyuiVector2 ttyui_vector2_subtract(TtyuiVector2 a, TtyuiVector2 b);
