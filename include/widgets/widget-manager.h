#pragma once

#include "widget.h"
#include "types/vector2.h"

#define TTYUI_WIDGET_MANAGER_STARTING_CAPACITY 5
#define TTYUI_WIDGET_MANAGER_CAPACITY_SCALE_FACTOR 2
#define TTYUI_WIDGET_MANAGER_DEFAULT_PADDING (Vector2) { 3, 1 }

typedef enum WidgetManagerSettingLayoutMode {
    LEFT_TO_RIGHT,
    TOP_TO_BOTTOM
} WidgetManagerSettingLayoutMode;

typedef struct WidgetManagerSettings {
    WidgetManagerSettingLayoutMode layout_mode;
} WidgetManagerSettings;

typedef struct WidgetManager {
    Vector2 position;
    Vector2 size;
    Vector2 padding;

    Widget** widgets;
    unsigned int widget_count;
    unsigned int widget_capacity;

    WidgetManagerSettings settings;
} WidgetManager;

WidgetManager ttyui_widget_manager_create(Vector2 start_position, Vector2 size, Vector2 padding);
void ttyui_widget_manager_add(WidgetManager* manager, Widget* widget);
void ttyui_widget_manager_update(WidgetManager* manager);
void ttyui_widget_manager_render(WidgetManager* manager, DisplayBuffer* display_buffer);
void ttyui_widget_manager_destroy(WidgetManager* manager);
