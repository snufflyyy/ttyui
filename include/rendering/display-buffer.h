#pragma once

#include <wchar.h>
#include <stdbool.h>

#include "rendering/cell/cell.h"
#include "rendering/cell/cell-style-manager.h"
#include "types/vector2.h"

typedef struct TtyuiDisplayBuffer {
    TtyuiCell** lines;
    TtyuiVector2 size;
} TtyuiDisplayBuffer;

TtyuiDisplayBuffer* ttyui_display_buffer_create(TtyuiVector2 size);
void ttyui_display_buffer_clear(TtyuiDisplayBuffer* buffer);
void ttyui_display_buffer_swap(TtyuiDisplayBuffer** a, TtyuiDisplayBuffer** b);
void ttyui_display_buffer_present(TtyuiDisplayBuffer* front, TtyuiDisplayBuffer* back, TtyuiCellStyleManager* cell_style_manager);
void ttyui_display_buffer_force_present(TtyuiDisplayBuffer* buffer, TtyuiCellStyleManager* cell_style_manager);
void ttyui_display_buffer_destroy(TtyuiDisplayBuffer* buffer);
