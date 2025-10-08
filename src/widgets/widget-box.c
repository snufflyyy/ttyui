#include "widgets/widget-box.h"

#include <stdio.h>
#include <stdlib.h>

#include "rendering/box.h"
#include "rendering/display-buffer.h"
#include "types/vector2.h"
#include "widgets/widget-manager.h"
#include "widgets/widget.h"

void ttyui_widget_box_update(void* widget_data);
void ttyui_widget_box_render(void* widget_data, TtyuiDisplayBuffer* display_buffer);
void ttyui_widget_box_destroy(void* widget_data);

TtyuiWidgetBox* ttyui_widget_box_create() {
    TtyuiWidgetBox* widget_box = (TtyuiWidgetBox*) malloc(sizeof(TtyuiWidgetBox));
    if (!widget_box) {
        fprintf(stderr, "[ERROR] [TTYUI] [BOX WIDGET] Failed to allocate memory for box widget!\n");
        return NULL;
    }

    widget_box->box = ttyui_box_create((TtyuiVector2) { 0, 0 }, (TtyuiVector2) { 0, 0 });
    widget_box->minimum_size = (TtyuiVector2) { 0, 0 };
    widget_box->maximum_size = (TtyuiVector2) { 0, 0 };
    widget_box->widget = (TtyuiWidget) { &widget_box->box.position, &widget_box->box.size, &widget_box->minimum_size, &widget_box->maximum_size, ttyui_widget_box_update, ttyui_widget_box_render, ttyui_widget_box_destroy };

    widget_box->widget_manager = ttyui_widget_manager_create(widget_box->box.position, widget_box->box.size, TTYUI_WIDGET_MANAGER_DEFAULT_PADDING);

    return widget_box;
}

void ttyui_widget_box_update(void* widget_data)  {
    TtyuiWidgetBox* widget_box = (TtyuiWidgetBox*) widget_data;

    widget_box->widget_manager.position = (TtyuiVector2) { widget_box->box.position.x, widget_box->box.position.y };
    widget_box->widget_manager.size = (TtyuiVector2) { widget_box->box.size.x, widget_box->box.size.y };
    if (widget_box->box.style.show_border) {
        widget_box->widget_manager.position = ttyui_vector2_add(widget_box->widget_manager.position, (TtyuiVector2) { 1, 1 });
        widget_box->widget_manager.size = ttyui_vector2_subtract(widget_box->widget_manager.size, (TtyuiVector2) { 2, 2 });
    }

    ttyui_widget_manager_update(&widget_box->widget_manager);
}

void ttyui_widget_box_render(void* widget_data, TtyuiDisplayBuffer* display_buffer) {
    TtyuiWidgetBox* widget_box = (TtyuiWidgetBox*) widget_data;
    ttyui_box_render(&widget_box->box, display_buffer);
    ttyui_widget_manager_render(&widget_box->widget_manager, display_buffer);
}

void ttyui_widget_box_destroy(void* widget_data)  {
    TtyuiWidgetBox* widget_box = (TtyuiWidgetBox*) widget_data;
    ttyui_widget_manager_destroy(&widget_box->widget_manager);
}
