#include "notifications/notification.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "cursor.h"
#include "box.h"
#include "types/vector2.h"

Notification* ttyui_notification_create(NotificationLevel level, const char* message) {
    Notification* notification = (Notification*) malloc(sizeof(Notification));
    if (!notification) {
        fprintf(stderr, "[ERROR] [TTYUI] [NOTIFICATION] Failed to allocate memory for notification\n");
        return NULL;
    }

    notification->padding = (Vector2) { 4, 1 }; // make const / make it macro
    notification->level = level;
    notification->message = message;
    notification->message_length = strnlen(message, MAX_MESSAGE_SIZE);
    notification->box.size = (Vector2) { (notification->padding.x * 2) + notification->message_length - 1, (notification->padding.y * 2) + 1 };

    return notification;
}

// the NotificationManager will each notifcation's position
void ttyui_notification_print(Notification* notification) {
    ttyui_save_cursor_position();

    ttyui_box_print(&notification->box);

    ttyui_set_cursor_position(notification->box.position.x + notification->padding.x, notification->box.position.y + (notification->box.size.y / 2) + 1);
    printf("%s", notification->message);

    ttyui_restore_cursor_position();
    fflush(stdout);
}

void ttyui_notification_destroy(Notification* notification) {
    free(notification);
}
