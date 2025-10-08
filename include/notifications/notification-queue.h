#pragma once

#include "notifications/notification.h"

#define TTYUI_NOTIFICATION_QUEUE_DEFAULT_CAPACITY 10
#define TTYUI_NOTIFICATION_QUEUE_CAPACITY_SCALE_FACTOR 2

typedef struct TtyuiNotificationQueue {
    TtyuiNotification** notifications;
    int length;
    int capacity;
} TtyuiNotificationQueue;

TtyuiNotificationQueue ttyui_notification_queue_create();
void ttyui_notification_queue_queue(TtyuiNotificationQueue* queue, TtyuiNotification* notification);
TtyuiNotification* ttyui_notification_queue_dequeue(TtyuiNotificationQueue* queue);
void ttyui_notification_queue_destroy(TtyuiNotificationQueue* queue);
