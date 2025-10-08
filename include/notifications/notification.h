#pragma once

#include <wchar.h>
#include <time.h>

#include "types/vector2.h"
#include "types/color.h"
#include "rendering/box.h"

#define TTYUI_NOTIFICATION_DEFAULT_PADDING (TtyuiVector2) { 3, 1 }
#define TTYUI_NOTIFICATION_MAX_MESSAGE_LENGTH 50
#define TTYUI_NOTIFICATION_DEFAULT_LIFETIME 5

typedef enum TtyuiNotificationLevel {
    TTYUI_NOTIFICATION_LEVEL_DEFAULT = TTYUI_COLOR_FOREGROUND_DEFAULT,
    TTYUI_NOTIFICATION_LEVEL_INFO = TTYUI_COLOR_FOREGROUND_BLUE,
    TTYUI_NOTIFICATION_LEVEL_SUCCESS = TTYUI_COLOR_FOREGROUND_GREEN,
    TTYUI_NOTIFICATION_LEVEL_WARNING = TTYUI_COLOR_FOREGROUND_YELLOW,
    TTYUI_NOTIFICATION_LEVEL_ERROR = TTYUI_COLOR_FOREGROUND_RED
} TtyuiNotificationLevel;

typedef struct TtyuiNotification {
    TtyuiBox box;
    TtyuiVector2 padding;

    TtyuiNotificationLevel level;

    time_t start_time;
    time_t lifetime;

    const wchar_t* message;
    unsigned int message_length;
} TtyuiNotification;

TtyuiNotification* ttyui_notification_create(TtyuiNotificationLevel level, const wchar_t* message);
void ttyui_notification_render(TtyuiNotification* notification, TtyuiDisplayBuffer* display_buffer);
void ttyui_notification_destroy(TtyuiNotification* notification);
