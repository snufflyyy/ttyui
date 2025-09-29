#include "ttyui.h"
#include "cursor.h"
#include "display-buffer.h"
#include "types/vector2.h"
#include "widgets/widget-manager.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <stdbool.h>
#include <locale.h>

static void ttyui_enable_raw_mode(Ttyui* ttyui) {
    if (tcgetattr(STDIN_FILENO, &ttyui->original_termios)) {
        perror("[ERROR] [TTYUI] Failed to get current terminos settings: ");
    }

    struct termios termios;
    cfmakeraw(&termios);
    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &termios)) {
        perror("[ERROR] [TTYUI] Failed to set terminal to raw mode: ");
    }
}

Ttyui* ttyui_create() {
    Ttyui* ttyui = (Ttyui*) malloc(sizeof(Ttyui));
    if (!ttyui) {
        fprintf(stderr, "[ERROR] [TTYUI] Failed to allocate memory for ttyui context!\n");
        return NULL;
    }

    struct winsize window_size;
    if (ioctl(0, TIOCGWINSZ, &window_size)) {
        perror("[ERROR] [TTYUI] Failed to get terminal size: ");
        return NULL;
    }
    ttyui->size = (Vector2) { window_size.ws_col, window_size.ws_row };

    // change to raw mode, this allows for keyboard input character by character, no echoing (printing) when a key is pressed,
    // special characters are treated normally, and there is very minimal output processing.
    ttyui_enable_raw_mode(ttyui);

    setlocale(LC_ALL, "");
    ttyui->front_buffer = ttyui_display_buffer_create(ttyui->size);
    ttyui->back_buffer = ttyui_display_buffer_create(ttyui->size);

    ttyui_cursor_hide();

    ttyui_display_buffer_force_present(ttyui->front_buffer);

    // makes STDIN_FILENO non blocking when using functions like read
    //int flags = fcntl(STDIN_FILENO, F_GETFL, 0);
    //fcntl(STDIN_FILENO, F_SETFL, flags | O_NONBLOCK);

    ttyui->widget_manager = ttyui_widget_manager_create((Vector2) { 0, 0 }, ttyui->size, TTYUI_WIDGET_MANAGER_DEFAULT_PADDING);

    ttyui->running = true;
    return ttyui;
}

void ttyui_update(Ttyui* ttyui) {
    ttyui_widget_manager_update(&ttyui->widget_manager);
}

void ttyui_render(Ttyui* ttyui) {
    ttyui_display_buffer_clear(ttyui->back_buffer);

    ttyui_widget_manager_render(&ttyui->widget_manager, ttyui->back_buffer);

    ttyui_display_buffer_present(ttyui->front_buffer, ttyui->back_buffer);
    ttyui_display_buffer_swap(&ttyui->front_buffer, &ttyui->back_buffer);
}

void ttyui_destroy(Ttyui* ttyui) {
    ttyui_display_buffer_destroy(ttyui->front_buffer);
    ttyui_display_buffer_destroy(ttyui->back_buffer);

    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &ttyui->original_termios)) {
        perror("[ERROR] [TTYUI] Failed to set terminal to cooked mode: ");
    }

    free(ttyui);
}
