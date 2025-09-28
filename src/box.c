#include "box.h"

#include <stdbool.h>

#include "display-buffer.h"
#include "types/vector2.h"

Box ttyui_box_create(Vector2 position, Vector2 size) {
    Box box = {0};

    box.position = position;
    box.size = size;
    box.show_border = true;

    return box;
}

void ttyui_box_render(Box* box, DisplayBuffer* display_buffer) {
    if (!box->show_border) { return; }

    // ╭─╮ │ ╰╯ | <- box drawing characters
    for (int y = box->position.y; y < box->position.y + box->size.y; y++) {
        for (int x = box->position.x; x < box->position.x + box->size.x; x++) {
            if (y == box->position.y && x == box->position.x) {
                display_buffer->lines[y][x] = L'╭';
            } else if (y == box->position.y && x == box->position.x + box->size.x - 1) {
                display_buffer->lines[y][x] = L'╮';
            } else if (y == box->position.y + box->size.y - 1 && x == box->position.x) {
                display_buffer->lines[y][x] = L'╰';
            } else if (y == box->position.y + box->size.y - 1 && x == box->position.x + box->size.x - 1) {
                display_buffer->lines[y][x] = L'╯';
            } else if (y == box->position.y || y == box->position.y + box->size.y - 1) {
                display_buffer->lines[y][x] = L'─';
            } else if (x == box->position.x || x == box->position.x + box->size.x - 1) {
                display_buffer->lines[y][x] = L'│';
            } else {
                display_buffer->lines[y][x] = L' ';
            }
        }
    }
}

void ttyui_box_destroy(Box* box) {
    // nothing for now!
}
