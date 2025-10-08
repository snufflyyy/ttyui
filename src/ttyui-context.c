#include "ttyui-context.h"
#include "notifications/notification-manager.h"
#include "rendering/cell/cell-style-manager.h"
#include "rendering/cursor.h"
#include "rendering/display-buffer.h"
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

static void ttyui_enable_raw_mode(TtyuiContext* ttyui) {
    if (tcgetattr(STDIN_FILENO, &ttyui->original_termios)) {
        perror("[ERROR] [TTYUI] Failed to get current terminos settings: ");
    }

    struct termios termios;
    cfmakeraw(&termios);
    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &termios)) {
        perror("[ERROR] [TTYUI] Failed to set terminal to raw mode: ");
    }
}

TtyuiContext* ttyui_create() {
    TtyuiContext* ttyui = (TtyuiContext*) malloc(sizeof(TtyuiContext));
    if (!ttyui) {
        fprintf(stderr, "[ERROR] [TTYUI] Failed to allocate memory for ttyui context!\n");
        return NULL;
    }

    struct winsize window_size;
    if (ioctl(0, TIOCGWINSZ, &window_size)) {
        perror("[ERROR] [TTYUI] Failed to get terminal size: ");
        return NULL;
    }
    ttyui->size = (TtyuiVector2) { window_size.ws_col, window_size.ws_row };

    // change to raw mode, this allows for keyboard input character by character, no echoing (printing) when a key is pressed,
    // special characters are treated normally, and there is very minimal output processing.
    ttyui_enable_raw_mode(ttyui);

    ttyui->cell_style_manager = ttyui_cell_style_manager_create();

    setlocale(LC_ALL, "");
    ttyui->front_buffer = ttyui_display_buffer_create(ttyui->size);
    ttyui->back_buffer = ttyui_display_buffer_create(ttyui->size);

    ttyui_cursor_hide();

    ttyui_display_buffer_force_present(ttyui->front_buffer, &ttyui->cell_style_manager);

    // makes STDIN_FILENO non blocking when using functions like read
    //int flags = fcntl(STDIN_FILENO, F_GETFL, 0);
    //fcntl(STDIN_FILENO, F_SETFL, flags | O_NONBLOCK);

    ttyui->widget_manager = ttyui_widget_manager_create((TtyuiVector2) { 0, 0 }, ttyui->size, TTYUI_WIDGET_MANAGER_DEFAULT_PADDING);

    ttyui->notification_manager = ttyui_notification_manager_create();

    ttyui->is_running = true;
    return ttyui;
}

void ttyui_update(TtyuiContext* ttyui) {
    ttyui_widget_manager_update(&ttyui->widget_manager);
}

void ttyui_render(TtyuiContext* ttyui) {
    ttyui_display_buffer_clear(ttyui->back_buffer);

    ttyui_widget_manager_render(&ttyui->widget_manager, ttyui->back_buffer);
    //ttyui_notification_manager_update_and_render(ttyui->notification_manager, ttyui->back_buffer);

    ttyui_display_buffer_present(ttyui->front_buffer, ttyui->back_buffer, &ttyui->cell_style_manager);
    ttyui_display_buffer_swap(&ttyui->front_buffer, &ttyui->back_buffer);
}

void ttyui_destroy(TtyuiContext* ttyui) {
    ttyui_widget_manager_destroy(&ttyui->widget_manager);

    ttyui_display_buffer_destroy(ttyui->front_buffer);
    ttyui_display_buffer_destroy(ttyui->back_buffer);

    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &ttyui->original_termios)) {
        perror("[ERROR] [TTYUI] Failed to set terminal to cooked mode: ");
    }

    free(ttyui);
}
