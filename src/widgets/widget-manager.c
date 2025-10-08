#include "widgets/widget-manager.h"
#include "rendering/display-buffer.h"
#include "types/vector2.h"
#include "widgets/widget.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

TtyuiWidgetManager ttyui_widget_manager_create(TtyuiVector2 start_position, TtyuiVector2 size, TtyuiVector2 padding) {
    TtyuiWidgetManager manager = {0};

    manager.position = start_position;
    manager.size = size;
    manager.padding = padding;

    manager.widget_capacity = TTYUI_WIDGET_MANAGER_STARTING_CAPACITY;
    manager.widgets = (TtyuiWidget**) malloc(sizeof(TtyuiWidget*) * manager.widget_capacity);

    return manager;
}

void ttyui_widget_manager_add(TtyuiWidgetManager* manager, TtyuiWidget* widget) {
    if (manager->widget_count + 1 >= manager->widget_capacity) {
        TtyuiWidget** temp = realloc(manager->widgets, sizeof(TtyuiWidget*) * (manager->widget_capacity * TTYUI_WIDGET_MANAGER_CAPACITY_SCALE_FACTOR));
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

/*
void ttyui_widget_manager_update(TtyuiWidgetManager* manager) {
    if (manager->widget_count <= 0) { return; }

    switch (manager->settings.layout_mode) {
        case TTYUI_WIDGET_MANAGER_LAYOUT_LEFT_TO_RIGHT: {
            int total_padding_x = (manager->widget_count - 1) * manager->padding.x + 2 * manager->padding.x;
            int available_width = manager->size.x - total_padding_x;
            int available_height = manager->size.y - 2 * manager->padding.y;

            for (int i = 0; i < manager->widget_count; i++) {
                TtyuiWidget* widget = manager->widgets[i];

                int target_width  = available_width / manager->widget_count;
                int target_height = available_height;

                // If widget dimension is 0 -> take all available space
                if (widget->minimum_size->x == 0 && widget->maximum_size->x == 0)
                    target_width = available_width;
                else {
                    if (widget->minimum_size->x > 0)
                        target_width = (int)fmax(widget->minimum_size->x, target_width);
                    if (widget->maximum_size->x > 0)
                        target_width = (int)fmin(widget->maximum_size->x, target_width);
                }

                if (widget->minimum_size->y == 0 && widget->maximum_size->y == 0)
                    target_height = available_height;
                else {
                    if (widget->minimum_size->y > 0)
                        target_height = (int)fmax(widget->minimum_size->y, target_height);
                    if (widget->maximum_size->y > 0)
                        target_height = (int)fmin(widget->maximum_size->y, target_height);
                }

                widget->size->x = target_width;
                widget->size->y = target_height;

                // Compute position (accumulate previous widths)
                widget->position->x = manager->position.x + manager->padding.x;
                for (int j = 0; j < i; j++) {
                    widget->position->x += manager->widgets[j]->size->x + manager->padding.x;
                }
                widget->position->y = manager->position.y + manager->padding.y;

                widget->ttyui_widget_update(widget);
            }
        } break;

        case TTYUI_WIDGET_MANAGER_LAYOUT_TOP_TO_BOTTOM: {
            int total_padding_y = (manager->widget_count - 1) * manager->padding.y + 2 * manager->padding.y;
            int available_height = manager->size.y - total_padding_y;
            int available_width  = manager->size.x - 2 * manager->padding.x;

            for (int i = 0; i < manager->widget_count; i++) {
                TtyuiWidget* widget = manager->widgets[i];

                int target_width  = available_width;
                int target_height = available_height / manager->widget_count;

                // If widget dimension is 0 -> take all available space
                if (widget->minimum_size->x == 0 && widget->maximum_size->x == 0)
                    target_width = available_width;
                else {
                    if (widget->minimum_size->x > 0)
                        target_width = (int)fmax(widget->minimum_size->x, target_width);
                    if (widget->maximum_size->x > 0)
                        target_width = (int)fmin(widget->maximum_size->x, target_width);
                }

                if (widget->minimum_size->y == 0 && widget->maximum_size->y == 0)
                    target_height = available_height;
                else {
                    if (widget->minimum_size->y > 0)
                        target_height = (int)fmax(widget->minimum_size->y, target_height);
                    if (widget->maximum_size->y > 0)
                        target_height = (int)fmin(widget->maximum_size->y, target_height);
                }

                widget->size->x = target_width;
                widget->size->y = target_height;

                // Compute position (accumulate previous heights)
                widget->position->x = manager->position.x + manager->padding.x;
                widget->position->y = manager->position.y + manager->padding.y;
                for (int j = 0; j < i; j++) {
                    widget->position->y += manager->widgets[j]->size->y + manager->padding.y;
                }

                widget->ttyui_widget_update(widget);
            }
        } break;
    }
}
*/

void ttyui_widget_manager_update(TtyuiWidgetManager* manager) {
    if (manager->widget_count <= 0) { return; }

    TtyuiVector2 total_padding = { (manager->widget_count - 1) * manager->padding.x + manager->padding.x * 2, (manager->widget_count - 1) * manager->padding.y + manager->padding.y * 2 };

    for (int i = 0; i < manager->widget_count; i++) {
        TtyuiWidget* widget = manager->widgets[i];

        switch (manager->settings.layout_mode) {
            case TTYUI_WIDGET_MANAGER_LAYOUT_LEFT_TO_RIGHT: {
                TtyuiVector2 available_size = (TtyuiVector2) { manager->size.x - total_padding.x, manager->size.y - (manager->padding.y * 2) };
                TtyuiVector2 target_size = (TtyuiVector2) { available_size.x / manager->widget_count , available_size.y };

                if (widget->minimum_size->x <= 0 && widget->maximum_size->x <= 0) {
                    target_size.x = available_size.x;
                } else {
                    target_size.x = (int) fmax(widget->minimum_size->x, target_size.x);
                }

                *widget->size = target_size;
                *widget->position = (TtyuiVector2) { manager->position.x + manager->padding.x, manager->position.y + manager->padding.y };
                for (int j = 0; j < i; j++) {
                    widget->position->x += manager->widgets[j]->size->x + manager->padding.x;
                }
            } break;
            case TTYUI_WIDGET_MANAGER_LAYOUT_TOP_TO_BOTTOM: {
                TtyuiVector2 available_size = (TtyuiVector2) { manager->size.x - (manager->padding.x * 2), manager->size.y - total_padding.y };
                TtyuiVector2 target_size = (TtyuiVector2) { available_size.x, available_size.y / manager->widget_count };

                if (widget->minimum_size->y <= 0 && widget->maximum_size->y <= 0) {
                    target_size.y = available_size.y;
                } else {
                    target_size.y = (int) fmin(widget->minimum_size->y, target_size.y);
                }

                *widget->size = target_size;
                *widget->position = (TtyuiVector2) { manager->position.x + manager->padding.x, manager->position.y + manager->padding.y };
                for (int j = 0; j < i; j++) {
                    widget->position->y += manager->widgets[j]->size->y + manager->padding.y;
                }
            } break;
            default: break;
        }

        widget->ttyui_widget_update(widget);
    }
}

void ttyui_widget_manager_render(TtyuiWidgetManager* manager, TtyuiDisplayBuffer* display_buffer) {
    for (int i = 0; i < manager->widget_count; i++) {
        manager->widgets[i]->ttyui_widget_render(manager->widgets[i], display_buffer);
    }
}

void ttyui_widget_manager_destroy(TtyuiWidgetManager* manager) {
    for (int i = 0; i < manager->widget_count; i++) {
        manager->widgets[i]->ttyui_widget_destroy(manager->widgets[i]);
    }
}
