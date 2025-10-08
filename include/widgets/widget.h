#pragma once

#include "rendering/display-buffer.h"
#include "types/vector2.h"

typedef struct TtyuiWidget {
    TtyuiVector2* position;
    TtyuiVector2* size;

    TtyuiVector2* minimum_size;
    TtyuiVector2* maximum_size;

    void (*ttyui_widget_update)(void* widget_data);
    void (*ttyui_widget_render)(void* widget_data, TtyuiDisplayBuffer* display_buffer);
    void (*ttyui_widget_destroy)(void* widget_data);
} TtyuiWidget;
