#pragma once

#include <stdbool.h>
#include <termios.h>

#include "display-buffer.h"
#include "widgets/widget-manager.h"

typedef struct Ttyui {
    bool running;
    Vector2 size;

    struct termios original_termios;

    DisplayBuffer* front_buffer;
    DisplayBuffer* back_buffer;

    WidgetManager widget_manager;
} Ttyui;

Ttyui* ttyui_create();
void ttyui_update(Ttyui* ttyui);
void ttyui_render(Ttyui* ttyui);
void ttyui_destroy(Ttyui* ttyui);
