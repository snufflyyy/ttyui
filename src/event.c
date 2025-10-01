#include "event.h"

#include <stdio.h>
#include <unistd.h>

TtyuiEvent ttyui_event_get() {
    TtyuiEvent event;

    char input[TTYUI_EVENT_MAX_INPUT_SIZE];
    if (read(STDIN_FILENO, input, TTYUI_EVENT_MAX_INPUT_SIZE) == -1) {
        perror("[ERROR] [TTYUI] [EVENT] Failed to read from stdin");
        return TTYUI_EVENT_ERROR;
    }

    switch (input[0]) {
        case 'q': return TTYUI_EVENT_QUIT; break;
        default: return TTYUI_EVENT_NONE; break;
    }

    return event;
}
