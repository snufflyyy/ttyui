#include "rendering/display-buffer.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "rendering/cell/cell-style-manager.h"
#include "rendering/cell/cell.h"
#include "types/vector2.h"
#include "rendering/cursor.h"

TtyuiDisplayBuffer* ttyui_display_buffer_create(TtyuiVector2 size) {
    TtyuiDisplayBuffer* buffer = (TtyuiDisplayBuffer*) malloc(sizeof(TtyuiDisplayBuffer));
    if (!buffer) {
        fprintf(stderr, "[ERROR] [TTYUI] [DISPLAY BUFFER] Failed to allocate memory for display buffer!\n");
        return NULL;
    }

    buffer->lines = (TtyuiCell**) malloc(sizeof(TtyuiCell*) * size.y);
    if (!buffer->lines) {
        fprintf(stderr, "[ERROR] [TTYUI] [DISPLAY BUFFER] Failed to allocate memory for display buffer's data!\n");
        free(buffer);
        return NULL;
    }

    for (int y = 0; y < size.y; y++) {
        buffer->lines[y] = (TtyuiCell*) malloc(sizeof(TtyuiCell) * size.x);
        if (!buffer->lines[y]) {
            fprintf(stderr, "[ERROR] [TTYUI] [DISPLAY BUFFER] Failed to allocate memory for display buffer's data!\n");
            free(buffer->lines);
            free(buffer);
            return NULL;
        }

        for (int x = 0; x < size.x; x++) {
            buffer->lines[y][x] = ttyui_cell_create();
        }
    }

    buffer->size = size;

    return buffer;
}

void ttyui_display_buffer_clear(TtyuiDisplayBuffer* buffer) {
    for (int y = 0; y < buffer->size.y; y++) {
        for (int x = 0; x < buffer->size.x; x++) {
            buffer->lines[y][x] = ttyui_cell_create();
        }
    }
}

void ttyui_display_buffer_swap(TtyuiDisplayBuffer** a, TtyuiDisplayBuffer** b) {
    TtyuiDisplayBuffer* temp = *a;
    *a = *b;
    *b = temp;
}

void ttyui_display_buffer_present(TtyuiDisplayBuffer* front, TtyuiDisplayBuffer* back, TtyuiCellStyleManager* cell_style_manager) {
    for (int y = 0; y < back->size.y; y++) {
        if (memcmp(back->lines[y], front->lines[y], front->size.x * sizeof(TtyuiCell)) != 0) {
            ttyui_cursor_set_position(0, y);
            for (int x = 0; x < back->size.x; x++) {
                ttyui_cell_print(&back->lines[y][x], cell_style_manager);
            }
            memcpy(front->lines[y], back->lines[y], front->size.x * sizeof(TtyuiCell));
        }
    }
    ttyui_cursor_set_position(0, 0);
    fflush(stdout);
}

void ttyui_display_buffer_force_present(TtyuiDisplayBuffer* buffer, TtyuiCellStyleManager* cell_style_manager) {
    for (int y = 0; y < buffer->size.y; y++) {
        ttyui_cursor_set_position(0, y);
        for (int x = 0; x < buffer->size.x; x++) {
            ttyui_cell_print(&buffer->lines[y][x], cell_style_manager);
        }
    }
    ttyui_cursor_set_position(0, 0);
    fflush(stdout);
}

void ttyui_display_buffer_destroy(TtyuiDisplayBuffer* buffer) {
    for (int i = 0; i < buffer->size.y; i++) {
        free(buffer->lines[i]);
    }
    free(buffer->lines);
    free(buffer);
}
