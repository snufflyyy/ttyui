#pragma once

#include "display-buffer.h"
#include "types/vector2.h"

typedef struct Widget {
    Vector2* position;
    Vector2* size;

    void (*ttyui_widget_update)(void* widget_data);
    void (*ttyui_widget_render)(void* widget_data, DisplayBuffer* display_buffer);
    void (*ttyui_widget_destroy)(void* widget_data);
} Widget;
