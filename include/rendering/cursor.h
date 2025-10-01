#pragma once

void ttyui_cursor_set_position(int line, int column);

void ttyui_cursor_move_up(int times);
void ttyui_cursor_move_down(int times);
void ttyui_cursor_move_left(int times);
void ttyui_cursor_move_right(int times);

void ttyui_cursor_save_position();
void ttyui_cursor_restore_position();

void ttyui_cursor_hide();
void ttyui_cursor_show();
