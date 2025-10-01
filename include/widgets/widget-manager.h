#pragma once

#include "types/vector2.h"
#include "widget.h"

#define TTYUI_WIDGET_MANAGER_STARTING_CAPACITY 5
#define TTYUI_WIDGET_MANAGER_CAPACITY_SCALE_FACTOR 2
#define TTYUI_WIDGET_MANAGER_DEFAULT_PADDING (TtyuiVector2) { 3, 1 }

typedef enum TtyuiWidgetManagerSettingLayoutMode {
    LEFT_TO_RIGHT,
    TOP_TO_BOTTOM
} TtyuiWidgetManagerSettingLayoutMode;

typedef struct TtyuiWidgetManagerSettings {
    TtyuiWidgetManagerSettingLayoutMode layout_mode;
} TtyuiWidgetManagerSettings;

typedef struct WidgetManager {
    TtyuiVector2 position;
    TtyuiVector2 size;
    TtyuiVector2 padding;

    TtyuiWidget** widgets;
    unsigned int widget_count;
    unsigned int widget_capacity;

    TtyuiWidgetManagerSettings settings;
} TtyuiWidgetManager;

TtyuiWidgetManager ttyui_widget_manager_create(TtyuiVector2 start_position, TtyuiVector2 size, TtyuiVector2 padding);
void ttyui_widget_manager_add(TtyuiWidgetManager* manager, TtyuiWidget* widget);
void ttyui_widget_manager_update(TtyuiWidgetManager* manager);
void ttyui_widget_manager_render(TtyuiWidgetManager* manager, TtyuiDisplayBuffer* display_buffer);
void ttyui_widget_manager_destroy(TtyuiWidgetManager* manager);
