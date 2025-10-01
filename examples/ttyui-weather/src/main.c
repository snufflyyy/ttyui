#include <stdbool.h>
#include <unistd.h>

#include "ttyui.h"

int main() {
    TtyuiContext* ttyui_context = ttyui_create();

    ttyui_widget_manager_add(&ttyui_context->widget_manager, (TtyuiWidget*) ttyui_widget_box_create());

    while (ttyui_context->is_running) {
        switch (ttyui_event_get()) {
            case TTYUI_EVENT_QUIT: ttyui_context->is_running = false; break;
            default: break;
        }
        ttyui_update(ttyui_context);
        ttyui_render(ttyui_context);
    }

    ttyui_destroy(ttyui_context);
}
