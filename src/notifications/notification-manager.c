#include "notifications/notification-manager.h"
#include "notifications/notification-queue.h"
#include "notifications/notification.h"

#include <stdio.h>
#include <stdlib.h>

NotificationManager* ttyui_notification_manager_create() {
    NotificationManager* manager = (NotificationManager*) malloc(sizeof(NotificationManager));
    if (!manager) {
        fprintf(stderr, "[ERROR] [TTYUI] [NOTIFICATION MANAGER] Failed to allocate memory for notification manager!\n");
        return NULL;
    }

    manager->queue = ttyui_notification_queue_create();

    return manager;
}

void ttyui_notification_manager_update(NotificationManager* manager) {
    int length = manager->queue.length;
    for (int i = 0; i < length; i++) {
        Notification* notification = ttyui_notification_queue_dequeue(&manager->queue);
        notification->box.position.y = notification->box.size.y * i;
        ttyui_notification_print(notification);
    }
}

void ttyui_notification_manager_destroy(NotificationManager* manager) {
    ttyui_notification_queue_destroy(&manager->queue);
    free(manager);
}
