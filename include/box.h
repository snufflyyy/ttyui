#pragma once

#include "display-buffer.h"
#include <types/vector2.h>

#define MAX_MESSAGE_SIZE 50

typedef struct Box {
    Vector2 position;
    Vector2 size;
    bool show_border;
} Box;

Box ttyui_box_create(Vector2 position, Vector2 size);
void ttyui_box_render(Box* box, DisplayBuffer* display_buffer);
void ttyui_box_destroy(Box* box);
