#include "display-buffer.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>

#include "cursor.h"
#include "ttyui.h"

DisplayBuffer* ttyui_display_buffer_create(Vector2 size) {
    DisplayBuffer* buffer = (DisplayBuffer*) malloc(sizeof(DisplayBuffer));
    if (!buffer) {
        fprintf(stderr, "[ERROR] [TTYUI] [DISPLAY BUFFER] Failed to allocate memory for display buffer!\n");
        return NULL;
    }

    buffer->lines = (wchar_t**) malloc(sizeof(wchar_t*) * size.y);
    if (!buffer->lines) {
        fprintf(stderr, "[ERROR] [TTYUI] [DISPLAY BUFFER] Failed to allocate memory for display buffer's data!\n");
        free(buffer);
        return NULL;
    }

    for (int i = 0; i < size.y; i++) {
        buffer->lines[i] = (wchar_t*) malloc(sizeof(wchar_t) * size.x);
        if (!buffer->lines[i]) {
            fprintf(stderr, "[ERROR] [TTYUI] [DISPLAY BUFFER] Failed to allocate memory for display buffer's data!\n");
            free(buffer->lines);
            free(buffer);
            return NULL;
        }

        wmemset(buffer->lines[i], L' ', size.x);
    }

    buffer->size = size;

    buffer->first_present = true;

    return buffer;
}

void ttyui_display_buffer_clear(DisplayBuffer* buffer) {
    for (int i = 0; i < buffer->size.y; i++) {
        wmemset(buffer->lines[i], L' ', buffer->size.x);
    }
}

void ttyui_display_buffer_swap(DisplayBuffer** a, DisplayBuffer** b) {
    DisplayBuffer* temp = *a;
    *a = *b;
    *b = temp;
}

void ttyui_display_buffer_present(DisplayBuffer* front, DisplayBuffer* back) {
    for (int i = 0; i < front->size.y; i++) {
        if (wmemcmp(back->lines[i], front->lines[i], front->size.x * sizeof(wchar_t)) != 0) {
            ttyui_set_cursor_position(0, i);
            wprintf(L"%.*ls", front->size.x, back->lines[i]);
            memcpy(front->lines[i], back->lines[i], front->size.x * sizeof(wchar_t));
        }
    }
    ttyui_set_cursor_position(0, 0);
    fflush(stdout);
}

void ttyui_display_buffer_force_present(DisplayBuffer* buffer) {
    for (int i = 0; i < buffer->size.y; i++) {
        ttyui_set_cursor_position(0, i);
        wprintf(L"%.*ls", buffer->size.x, buffer->lines[i]);
    }
    ttyui_set_cursor_position(0, 0);
    fflush(stdout);
}

void ttyui_display_buffer_destroy(DisplayBuffer* buffer) {
    for (int i = 0; i < buffer->size.y; i++) {
        free(buffer->lines[i]);
    }
    free(buffer->lines);
    free(buffer);
}
