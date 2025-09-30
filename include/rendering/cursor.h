#pragma once

// todo, change to fit function naming scheme (example: ttyui_cursor_move_up() instead of ttyui_move_cursor_up())

void ttyui_set_cursor_position(int line, int column);

void ttyui_move_cursor_up(int times);
void ttyui_move_cursor_down(int times);
void ttyui_move_cursor_left(int times);
void ttyui_move_cursor_right(int times);

void ttyui_save_cursor_position();
void ttyui_restore_cursor_position();

void ttyui_cursor_hide();
void ttyui_cursor_show();
