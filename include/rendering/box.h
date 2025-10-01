#pragma once

#include <stdbool.h>

#include "types/vector2.h"
#include "types/color.h"
#include "rendering/display-buffer.h"

typedef struct TtyuiBoxStyle {
    bool show_border;
    TtyuiForegroundColor border_color;
    TtyuiBackgroundColor background_color;
} TtyuiBoxStyle;

typedef struct TtyuiBox {
    TtyuiVector2 position;
    TtyuiVector2 size;

    TtyuiBoxStyle style;
} TtyuiBox;

TtyuiBox ttyui_box_create(TtyuiVector2 position, TtyuiVector2 size);
void ttyui_box_render(TtyuiBox* box, TtyuiDisplayBuffer* display_buffer);
