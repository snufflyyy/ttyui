#include "notifications/notification.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "rendering/box.h"
#include "rendering/display-buffer.h"
#include "types/vector2.h"

TtyuiNotification* ttyui_notification_create(TtyuiNotificationLevel level, const wchar_t* message) {
    TtyuiNotification* notification = (TtyuiNotification*) malloc(sizeof(TtyuiNotification));
    if (!notification) {
        fprintf(stderr, "[ERROR] [TTYUI] [NOTIFICATION] Failed to allocate memory for notification!\n");
        return NULL;
    }

    notification->box.position = (TtyuiVector2) { 0, 0 };
    notification->box.size = (TtyuiVector2) { 2 + (notification->padding.x * 2) + notification->message_length, 2 + (notification->padding.y * 2) + 1 };

    notification->padding = TTYUI_NOTIFICATION_DEFAULT_PADDING;
    notification->level = level;

    notification->lifetime = TTYUI_NOTIFICATION_DEFAULT_LIFETIME;

    notification->message = message;
    notification->message_length = wcslen(message);

    return notification;
}

void ttyui_notification_render(TtyuiNotification* notification, TtyuiDisplayBuffer* display_buffer) {
    ttyui_box_render(&notification->box, display_buffer);

    for (int i = 0; i < notification->message_length; i++) {
        display_buffer->lines[notification->box.position.y + notification->padding.y + 1][1 + notification->box.position.x + (notification->padding.x + i)].character = notification->message[i];
    }
}

void ttyui_notification_destroy(TtyuiNotification* notification) {
    free(notification);
}
