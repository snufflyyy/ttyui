#pragma once

#include "box.h"
#include "widget.h"
#include "widgets/widget-manager.h"

typedef struct WidgetBox {
    Widget widget;
    Box box;
    WidgetManager widget_manager;
} WidgetBox;

WidgetBox* ttyui_widget_box_create();
