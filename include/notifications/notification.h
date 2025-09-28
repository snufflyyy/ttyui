#pragma once

#include "types/vector2.h"
#include <box.h>

typedef enum NotificationLevel {
    INFO, // blue
    SUCCESS, // green
    WARNING, // yellow
    ERROR, // red
} NotificationLevel;

typedef struct Notification {
    Box box;
    Vector2 padding;

    NotificationLevel level;

    const char* message;
    unsigned int message_length;
} Notification;

Notification* ttyui_notification_create(NotificationLevel level, const char* message);
void ttyui_notification_print(Notification* notification);
void ttyui_notification_destroy(Notification* notification);
