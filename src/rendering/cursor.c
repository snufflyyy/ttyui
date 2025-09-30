#include "rendering/cursor.h"

#include <stdio.h>
#include <wchar.h>

inline void ttyui_set_cursor_position(int x, int y) {
    // for some reason, cursor positions do NOT start at 0, and instead begin at 1
    // this function assumes that x and y WILL BE zero-indexed
    wprintf(L"\033[%d;%dH", y + 1, x + 1);
}

inline void ttyui_move_cursor_up(int times) {
    wprintf(L"\033[%dA", times);
}

inline void ttyui_move_cursor_down(int times) {
    wprintf(L"\033[%dB", times);
}

inline void ttyui_move_cursor_left(int times) {
    wprintf(L"\033[%dD", times);
}

inline void ttyui_move_cursor_right(int times) {
    wprintf(L"\033[%dC", times);
}

inline void ttyui_save_cursor_position() {
    wprintf(L"\033[s");
}

inline void ttyui_restore_cursor_position() {
    wprintf(L"\033[u");
}

inline void ttyui_cursor_hide() {
    wprintf(L"\033[?25l");
}

inline void ttyui_cursor_show() {
    wprintf(L"\033[?25h");
}
