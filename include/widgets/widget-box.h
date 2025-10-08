#pragma once

#include "rendering/box.h"
#include "types/vector2.h"
#include "widget.h"
#include "widgets/widget-manager.h"

typedef struct TtyuiWidgetBox {
    TtyuiWidget widget;
    TtyuiWidgetManager widget_manager;

    TtyuiBox box;
    TtyuiVector2 minimum_size; // 0 in either diamention means no minimum
    TtyuiVector2 maximum_size; // 0 in either diamention means no maximum
} TtyuiWidgetBox;

TtyuiWidgetBox* ttyui_widget_box_create();

void ttyui_widget_box_update(void* widget_data);
void ttyui_widget_box_render(void* widget_data, TtyuiDisplayBuffer* display_buffer);
void ttyui_widget_box_destroy(void* widget_data);
