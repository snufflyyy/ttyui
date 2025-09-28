#include "notifications/notification-queue.h"

#include "notifications/notification.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

NotificationQueue ttyui_notification_queue_create() {
    NotificationQueue queue = {0};

    queue.notifications = (Notification**) malloc(sizeof(Notification*) * TTYUI_NOTIFICATION_QUEUE_DEFAULT_CAPACITY);
    queue.capacity = TTYUI_NOTIFICATION_QUEUE_DEFAULT_CAPACITY;
    queue.length = 0;

    return queue;
}

void ttyui_notification_queue_queue(NotificationQueue* queue, Notification* notification) {
    if (queue->length + 1 >= queue->capacity) {
        Notification** temp = (Notification**) realloc(queue->notifications, sizeof(Notification*) * (queue->capacity * TTYUI_NOTIFICATION_QUEUE_CAPACITY_SCALE_FACTOR));
        if (!temp) {
            fprintf(stderr, "[ERROR] [TTYUI] [NOTIFICATION QUEUE] Failed to reallocate memory for notification queue!\n");
            return;
        }

        queue->notifications = temp;
    }

    queue->notifications[queue->length] = notification;
    queue->length++;
}

Notification* ttyui_notification_queue_dequeue(NotificationQueue* queue) {
    if (queue->length < 0) {
        fprintf(stderr, "[WARN] [TTYUI] [NOTIFICATION QUEUE] Tried to dequeue from empty notification queue!\n");
        return NULL;
    }

    Notification* notification = queue->notifications[0];
    for (int i = 1; i < queue->length; i++) {
        queue->notifications[i - 1] = queue->notifications[i];
    }

    queue->length--;
    return notification;
}

void ttyui_notification_queue_destroy(NotificationQueue* queue) {
    for (int i = 0; i < queue->length; i++) {
        ttyui_notification_destroy(queue->notifications[i]);
    }

    free(queue->notifications);
    queue->notifications = NULL;
    queue->length = 0;
}
