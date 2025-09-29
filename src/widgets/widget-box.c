#include "widgets/widget-box.h"

#include <stdio.h>
#include <stdlib.h>

#include "box.h"
#include "display-buffer.h"
#include "types/vector2.h"
#include "widgets/widget-manager.h"
#include "widgets/widget.h"

static void ttyui_widget_box_update(void* widget_data);
static void ttyui_widget_box_render(void* widget_data, DisplayBuffer* display_buffer);
void ttyui_widget_box_destroy(void* widget_data);

WidgetBox* ttyui_widget_box_create() {
    WidgetBox* widget_box = (WidgetBox*) malloc(sizeof(WidgetBox));
    if (!widget_box) {
        fprintf(stderr, "[ERROR] [TTYUI] [BOX WIDGET] Failed to allocate memory for box widget!\n");
        return NULL;
    }

    widget_box->box = ttyui_box_create((Vector2) { 0, 0 }, (Vector2) { 0, 0 });
    widget_box->widget = (Widget) { &widget_box->box.position, &widget_box->box.size, ttyui_widget_box_update, ttyui_widget_box_render, ttyui_widget_box_destroy };

    widget_box->widget_manager = ttyui_widget_manager_create(widget_box->box.position, widget_box->box.size, TTYUI_WIDGET_MANAGER_DEFAULT_PADDING);

    return widget_box;
}

void ttyui_widget_box_update(void* widget_data)  {
    WidgetBox* widget_box = (WidgetBox*) widget_data;

    widget_box->widget_manager.position = (Vector2) { widget_box->box.position.x, widget_box->box.position.y };
    widget_box->widget_manager.size = (Vector2) { widget_box->box.size.x, widget_box->box.size.y };
    if (widget_box->box.show_border) {
        widget_box->widget_manager.position = ttyui_vector2_add(widget_box->widget_manager.position, (Vector2) { 1, 1 });
        widget_box->widget_manager.size = ttyui_vector2_subtract(widget_box->widget_manager.size, (Vector2) { 2, 2 });
    }

    ttyui_widget_manager_update(&widget_box->widget_manager);
}

void ttyui_widget_box_render(void* widget_data, DisplayBuffer* display_buffer) {
    WidgetBox* widget_box = (WidgetBox*) widget_data;
    ttyui_box_render(&widget_box->box, display_buffer);
    ttyui_widget_manager_render(&widget_box->widget_manager, display_buffer);
}

void ttyui_widget_box_destroy(void* widget_data)  {
    WidgetBox* widget_box = (WidgetBox*) widget_data;
    ttyui_box_destroy(&widget_box->box);
    ttyui_widget_manager_destroy(&widget_box->widget_manager);
}
