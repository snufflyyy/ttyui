#pragma once

#include "notifications/notification-queue.h"

typedef struct NotificationManager {
    NotificationQueue queue;
} NotificationManager;

NotificationManager* ttyui_notification_manager_create();
void ttyui_notification_manager_update(NotificationManager* manager);
void ttyui_notification_manager_destroy(NotificationManager* manager);
