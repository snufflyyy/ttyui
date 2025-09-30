#pragma once

#include <stdbool.h>

#include "types/vector2.h"
#include "types/color.h"
#include "rendering/display-buffer.h"

#define MAX_MESSAGE_SIZE 50

typedef struct Box {
    Vector2 position;
    Vector2 size;

    bool show_border;
    ForegroundColor border_color;
} Box;

Box ttyui_box_create(Vector2 position, Vector2 size);
void ttyui_box_render(Box* box, DisplayBuffer* display_buffer);
void ttyui_box_destroy(Box* box);
