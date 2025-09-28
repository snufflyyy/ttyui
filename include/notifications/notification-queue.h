#pragma once

#include "notifications/notification.h"

#define TTYUI_NOTIFICATION_QUEUE_DEFAULT_CAPACITY 10
#define TTYUI_NOTIFICATION_QUEUE_CAPACITY_SCALE_FACTOR 2

typedef struct NotificationQueue {
    Notification** notifications;
    int length;
    int capacity;
} NotificationQueue;

NotificationQueue ttyui_notification_queue_create();
void ttyui_notification_queue_queue(NotificationQueue* queue, Notification* notification);
Notification* ttyui_notification_queue_dequeue(NotificationQueue* queue);
void ttyui_notification_queue_destroy(NotificationQueue* queue);
