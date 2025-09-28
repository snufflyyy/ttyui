#include "widgets/widget-manager.h"
#include "display-buffer.h"
#include "types/vector2.h"
#include "widgets/widget.h"
#include <stdio.h>
#include <stdlib.h>

WidgetManager ttyui_widget_manager_create(Vector2 start_position, Vector2 size, Vector2 padding) {
    WidgetManager manager = {0};

    manager.position = start_position;
    manager.size = size;
    manager.padding = padding;

    manager.widget_capacity = TTYUI_WIDGET_MANAGER_STARTING_CAPACITY;
    manager.widgets = (Widget**) malloc(sizeof(Widget*) * manager.widget_capacity);

    return manager;
}

void ttyui_widget_manager_add(WidgetManager* manager, Widget* widget) {
    if (manager->widget_count + 1 >= manager->widget_capacity) {
        Widget** temp = realloc(manager->widgets, sizeof(Widget*) * (manager->widget_capacity * TTYUI_WIDGET_MANAGER_CAPACITY_SCALE_FACTOR));
        if (!temp) {
            fprintf(stderr, "[ERROR] [TTYUI] [WIDGET MANAGER] Failed to reallocate memory for widgets!\n");
            return;
        }

        manager->widgets = temp;
        manager->widget_capacity *= TTYUI_WIDGET_MANAGER_CAPACITY_SCALE_FACTOR;
    }

    manager->widgets[manager->widget_count] = widget;
    manager->widget_count++;
}

void ttyui_widget_manager_update(WidgetManager* manager) {
    if (manager->widget_count <= 0) { return; }

    int total_padding_x = manager->padding.x * (manager->widget_count + 1);
    int widget_width = (manager->size.x - total_padding_x) / manager->widget_count;
    int widget_height = manager->size.y - (manager->padding.y * 2);

    for (int i = 0; i < manager->widget_count; i++) {
        manager->widgets[i]->size->x = widget_width;
        manager->widgets[i]->size->y = widget_height;

        manager->widgets[i]->position->x = manager->position.x + manager->padding.x + i * (widget_width + manager->padding.x);
        manager->widgets[i]->position->y = manager->position.y + manager->padding.y;

        manager->widgets[i]->ttyui_widget_update(manager->widgets[i]);
    }
}

void ttyui_widget_manager_render(WidgetManager* manager, DisplayBuffer* display_buffer) {
    for (int i = 0; i < manager->widget_count; i++) {
        manager->widgets[i]->ttyui_widget_render(manager->widgets[i], display_buffer);
    }
}

void ttyui_widget_manager_destroy(WidgetManager* manager) {
    for (int i = 0; i < manager->widget_count; i++) {
        manager->widgets[i]->ttyui_widget_destroy(manager->widgets[i]);
    }
}
