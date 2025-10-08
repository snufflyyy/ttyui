#include "notifications/notification-queue.h"

#include "notifications/notification.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

TtyuiNotificationQueue ttyui_notification_queue_create() {
    TtyuiNotificationQueue queue = {0};

    queue.notifications = (TtyuiNotification**) malloc(sizeof(TtyuiNotification*) * TTYUI_NOTIFICATION_QUEUE_DEFAULT_CAPACITY);
    queue.capacity = TTYUI_NOTIFICATION_QUEUE_DEFAULT_CAPACITY;
    queue.length = 0;

    return queue;
}

void ttyui_notification_queue_queue(TtyuiNotificationQueue* queue, TtyuiNotification* notification) {
    if (queue->length + 1 >= queue->capacity) {
        TtyuiNotification** temp = (TtyuiNotification**) realloc(queue->notifications, sizeof(TtyuiNotification*) * (queue->capacity * TTYUI_NOTIFICATION_QUEUE_CAPACITY_SCALE_FACTOR));
        if (!temp) {
            fprintf(stderr, "[ERROR] [TTYUI] [NOTIFICATION QUEUE] Failed to reallocate memory for notification queue!\n");
            return;
        }

        queue->notifications = temp;
    }

    queue->notifications[queue->length] = notification;
    queue->length++;
}

TtyuiNotification* ttyui_notification_queue_dequeue(TtyuiNotificationQueue* queue) {
    if (queue->length < 0) {
        fprintf(stderr, "[WARN] [TTYUI] [NOTIFICATION QUEUE] Tried to dequeue from empty notification queue!\n");
        return NULL;
    }

    TtyuiNotification* notification = queue->notifications[0];
    for (int i = 1; i < queue->length; i++) {
        queue->notifications[i - 1] = queue->notifications[i];
    }

    queue->length--;
    return notification;
}

void ttyui_notification_queue_destroy(TtyuiNotificationQueue* queue) {
    for (int i = 0; i < queue->length; i++) {
        ttyui_notification_destroy(queue->notifications[i]);
    }

    free(queue->notifications);
    queue->notifications = NULL;
    queue->length = 0;
}
