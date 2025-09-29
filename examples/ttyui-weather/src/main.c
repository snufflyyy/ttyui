#include <stdbool.h>
#include <unistd.h>

#include "ttyui.h"
#include "widgets/widget-box.h"
#include "widgets/widget-manager.h"

int main() {
    Ttyui* ttyui_context = ttyui_create();

    ttyui_widget_manager_add(&ttyui_context->widget_manager, (Widget*) ttyui_widget_box_create());
    ttyui_widget_manager_add(&((WidgetBox*) ttyui_context->widget_manager.widgets[0])->widget_manager, (Widget*) ttyui_widget_box_create());
    ttyui_widget_manager_add(&((WidgetBox*) ttyui_context->widget_manager.widgets[0])->widget_manager, (Widget*) ttyui_widget_box_create());

    ttyui_widget_manager_add(&ttyui_context->widget_manager, (Widget*) ttyui_widget_box_create());
    ttyui_widget_manager_add(&((WidgetBox*) ttyui_context->widget_manager.widgets[1])->widget_manager, (Widget*) ttyui_widget_box_create());
    ttyui_widget_manager_add(&((WidgetBox*) ttyui_context->widget_manager.widgets[1])->widget_manager, (Widget*) ttyui_widget_box_create());

    char event[3];
    while (ttyui_context->running) {
        read(STDIN_FILENO, &event, 3);
        switch (event[0]) {
            case 'q': ttyui_context->running = false; break;
            case '\033':
                switch (event[2]) {

                }
                break;
        }

        ttyui_update(ttyui_context);
        ttyui_render(ttyui_context);
    }

    ttyui_destroy(ttyui_context);
}
