#pragma once

#include <wchar.h>
#include <stdbool.h>

#include "rendering/cell/cell.h"
#include "rendering/cell/cell-style-manager.h"
#include "types/vector2.h"

typedef struct DisplayBuffer {
    Cell** lines;
    Vector2 size;
} DisplayBuffer;

DisplayBuffer* ttyui_display_buffer_create(Vector2 size);
void ttyui_display_buffer_clear(DisplayBuffer* buffer);
void ttyui_display_buffer_swap(DisplayBuffer** a, DisplayBuffer** b);
void ttyui_display_buffer_present(DisplayBuffer* front, DisplayBuffer* back, CellStyleManager* cell_style_manager);
void ttyui_display_buffer_force_present(DisplayBuffer* buffer, CellStyleManager* cell_style_manager);
void ttyui_display_buffer_destroy(DisplayBuffer* buffer);
