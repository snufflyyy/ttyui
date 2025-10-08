#include "rendering/box.h"

#include <stdbool.h>

#include "rendering/display-buffer.h"
#include "types/color.h"
#include "types/vector2.h"

TtyuiBox ttyui_box_create(TtyuiVector2 position, TtyuiVector2 size) {
    TtyuiBox box = {0};

    box.position = position;
    box.size = size;

    box.style = (TtyuiBoxStyle) { .show_border = true, .border_color = TTYUI_COLOR_FOREGROUND_DEFAULT, .background_color= TTYUI_COLOR_BACKGROUND_DEFAULT };

    return box;
}

void ttyui_box_render(TtyuiBox* box, TtyuiDisplayBuffer* display_buffer) {
    // ─│╭╮╰╯┴ box drawing characters
    //
    // Tab box (maybe) example:
    //   ╭─ Week ─╮ ╭─ Month ─╮
    // ╭─╯        ╰─┴─────────┴───────────────
    // │ This is an example of the first tab.
    // │
    //
    //   ╭─ Week ─╮ ╭─ Month ─╮
    // ╭─┴────────┴─╯         ╰────────────────
    // │ This is an example of the second tab.
    // │

    for (int y = box->position.y; y < box->position.y + box->size.y; y++) {
        for (int x = box->position.x; x < box->position.x + box->size.x; x++) {
            if (!box->style.show_border) {
                display_buffer->lines[y][x].character = L' ';
                display_buffer->lines[y][x].style.background_color = box->style.background_color;
                continue;
            }

            if (y == box->position.y && x == box->position.x) {
                display_buffer->lines[y][x].character = L'╭';
                display_buffer->lines[y][x].style.foreground_color = box->style.border_color;
            } else if (y == box->position.y && x == box->position.x + box->size.x - 1) {
                display_buffer->lines[y][x].character = L'╮';
                display_buffer->lines[y][x].style.foreground_color = box->style.border_color;
            } else if (y == box->position.y + box->size.y - 1 && x == box->position.x) {
                display_buffer->lines[y][x].character = L'╰';
                display_buffer->lines[y][x].style.foreground_color = box->style.border_color;
            } else if (y == box->position.y + box->size.y - 1 && x == box->position.x + box->size.x - 1) {
                display_buffer->lines[y][x].character = L'╯';
                display_buffer->lines[y][x].style.foreground_color = box->style.border_color;
            } else if (y == box->position.y || y == box->position.y + box->size.y - 1) {
                display_buffer->lines[y][x].character = L'─';
                display_buffer->lines[y][x].style.foreground_color = box->style.border_color;
            } else if (x == box->position.x || x == box->position.x + box->size.x - 1) {
                display_buffer->lines[y][x].character = L'│';
                display_buffer->lines[y][x].style.foreground_color = box->style.border_color;
            } else {
                display_buffer->lines[y][x].character = L' ';
                display_buffer->lines[y][x].style.background_color = box->style.background_color;
            }
        }
    }
}
