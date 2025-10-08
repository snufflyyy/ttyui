#pragma once

#include "notifications/notification-queue.h"
#include "notifications/notification.h"
#include "types/vector2.h"

#define TTYUI_NOTIFICATION_MANAGER_DEFAULT_PADDING (TtyuiVector2) { 3, 1 }
#define TTYUI_NOTIFICATION_MANAGER_MAX_ON_SCREEN_NOTIFICATIONS 5

typedef struct TtyuiNotificationManager {
    TtyuiNotificationQueue queue;

    TtyuiVector2 padding;
    TtyuiNotification* on_screen_notifications[TTYUI_NOTIFICATION_MANAGER_MAX_ON_SCREEN_NOTIFICATIONS];
    unsigned int on_screen_notification_count;
} TtyuiNotificationManager;

TtyuiNotificationManager* ttyui_notification_manager_create();
void ttyui_notification_manager_update_and_render(TtyuiNotificationManager* manager, TtyuiDisplayBuffer* display_buffer);
void ttyui_notification_manager_destroy(TtyuiNotificationManager* manager);
