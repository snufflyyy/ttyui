#pragma once

#include <wchar.h>
#include <stdbool.h>

#include "types/vector2.h"

typedef struct DisplayBuffer {
    wchar_t** lines;
    Vector2 size;

    bool first_present;
} DisplayBuffer;

DisplayBuffer* ttyui_display_buffer_create(Vector2 size);
void ttyui_display_buffer_clear(DisplayBuffer* buffer);
void ttyui_display_buffer_swap(DisplayBuffer** a, DisplayBuffer** b);
void ttyui_display_buffer_present(DisplayBuffer* front, DisplayBuffer* back);
void ttyui_display_buffer_force_present(DisplayBuffer* buffer);
void ttyui_display_buffer_destroy(DisplayBuffer* buffer);
