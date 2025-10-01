#pragma once

#include "rendering/box.h"
#include "widget.h"
#include "widgets/widget-manager.h"

typedef struct WidgetBox {
    TtyuiWidget widget;
    TtyuiBox box;
    TtyuiWidgetManager widget_manager;
} TtyuiWidgetBox;

TtyuiWidgetBox* ttyui_widget_box_create();
