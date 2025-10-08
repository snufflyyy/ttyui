#include "notifications/notification-manager.h"
#include "notifications/notification-queue.h"
#include "notifications/notification.h"
#include "rendering/display-buffer.h"
#include "widgets/widget-manager.h"

#include <stdio.h>
#include <stdlib.h>

TtyuiNotificationManager* ttyui_notification_manager_create() {
    TtyuiNotificationManager* manager = (TtyuiNotificationManager*) malloc(sizeof(TtyuiNotificationManager));
    if (!manager) {
        fprintf(stderr, "[ERROR] [TTYUI] [NOTIFICATION MANAGER] Failed to allocate memory for notification manager!\n");
        return NULL;
    }

    manager->queue = ttyui_notification_queue_create();
    manager->padding = TTYUI_NOTIFICATION_MANAGER_DEFAULT_PADDING;
    manager->on_screen_notification_count = 0;

    return manager;
}

void ttyui_notification_manager_update_and_render(TtyuiNotificationManager* manager, TtyuiDisplayBuffer* display_buffer) {
    manager->on_screen_notifications[manager->on_screen_notification_count] = ttyui_notification_queue_dequeue(&manager->queue);
    manager->on_screen_notification_count++;

    TtyuiNotification* notification = manager->on_screen_notifications[manager->on_screen_notification_count];
    notification->box.position.y = notification->box.size.y * ((manager->on_screen_notification_count - 1) + manager->padding.y);
    notification->box.position.x = display_buffer->size.x - manager->padding.x - notification->box.size.x;

    for (int i = 0; i < manager->queue.length; i++) {
        ttyui_notification_render(notification, display_buffer);
    }
}

void ttyui_notification_manager_destroy(TtyuiNotificationManager* manager) {
    ttyui_notification_queue_destroy(&manager->queue);
    free(manager);
}
