#pragma once

#define TTYUI_EVENT_MAX_INPUT_SIZE 3

typedef enum Event {
    TTYUI_EVENT_NONE,
    TTYUI_EVENT_ERROR,
    TTYUI_EVENT_QUIT,
} TtyuiEvent;

TtyuiEvent ttyui_event_get();
