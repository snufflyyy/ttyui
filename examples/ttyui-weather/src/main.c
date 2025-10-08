#include "ttyui.h"

int main() {
    TtyuiContext* ttyui_context = ttyui_create();



    /*
    ttyui_context->widget_manager.settings.layout_mode = TTYUI_WIDGET_MANAGER_LAYOUT_TOP_TO_BOTTOM;

    ttyui_widget_manager_add(&ttyui_context->widget_manager, (TtyuiWidget*) ttyui_widget_box_create());
    TtyuiWidgetBox* top_widget = (TtyuiWidgetBox*) ttyui_context->widget_manager.widgets[0];
    top_widget->box.style.show_border = false;

    ttyui_widget_manager_add(&ttyui_context->widget_manager, (TtyuiWidget*) ttyui_widget_box_create());
    TtyuiWidgetBox* bottom_widget = (TtyuiWidgetBox*) ttyui_context->widget_manager.widgets[1];
    bottom_widget->widget_manager.settings.layout_mode = TTYUI_WIDGET_MANAGER_LAYOUT_TOP_TO_BOTTOM;
    bottom_widget->widget_manager.padding = (TtyuiVector2) { 0, 0 };

    ttyui_widget_manager_add(&bottom_widget->widget_manager, (TtyuiWidget*) ttyui_widget_box_create());
    TtyuiWidgetBox* bottom_top_widget = (TtyuiWidgetBox*) bottom_widget->widget_manager.widgets[0];
    //bottom_top_widget->maximum_size = (TtyuiVector2) { 0, 3 };

    ttyui_widget_manager_add(&bottom_widget->widget_manager, (TtyuiWidget*) ttyui_widget_box_create());
    TtyuiWidgetBox* bottom_bottom_widget = (TtyuiWidgetBox*) bottom_widget->widget_manager.widgets[1];

    for (int i = 0; i < 7; i++) {
        ttyui_widget_manager_add(&bottom_bottom_widget->widget_manager, (TtyuiWidget*) ttyui_widget_box_create());
    }
    */

    while (ttyui_context->is_running) {
        switch (ttyui_event_get()) {
            case TTYUI_EVENT_QUIT: ttyui_context->is_running = false; break;
            //case TTYUI_EVENT_KEY_N: ttyui_notification_queue_queue(&ttyui_context->notification_manager->queue, ttyui_notification_create(TTYUI_NOTIFICATION_LEVEL_DEFAULT, L"test"));
            default: break;
        }
        ttyui_update(ttyui_context);
        ttyui_render(ttyui_context);
    }

    ttyui_destroy(ttyui_context);
}
