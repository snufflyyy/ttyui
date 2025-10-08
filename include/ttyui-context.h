#pragma once

#include <stdbool.h>
#include <termios.h>

#include "rendering/cell/cell-style-manager.h"
#include "rendering/display-buffer.h"
#include "widgets/widget-manager.h"
#include "notifications/notification-manager.h"

typedef struct TtyuiContext {
    bool is_running;
    TtyuiVector2 size;

    struct termios original_termios;

    TtyuiCellStyleManager cell_style_manager;
    TtyuiDisplayBuffer* front_buffer;
    TtyuiDisplayBuffer* back_buffer;

    TtyuiWidgetManager widget_manager;

    TtyuiNotificationManager* notification_manager;
} TtyuiContext;

TtyuiContext* ttyui_create();
void ttyui_update(TtyuiContext* ttyui);
void ttyui_render(TtyuiContext* ttyui);
void ttyui_destroy(TtyuiContext* ttyui);
