#include "rendering/cell/cell.h"
#include "rendering/cell/cell-style-manager.h"
#include "types/color.h"

#include <wchar.h>

inline TtyuiCell ttyui_cell_create() {
    return (TtyuiCell) { L' ', (TtyuiCellStyle) { TTYUI_COLOR_BACKGROUND_DEFAULT, TTYUI_COLOR_FOREGROUND_DEFAULT, TTYUI_CELL_PROPERTY_NONE } };
}

void ttyui_cell_print(TtyuiCell* cell, TtyuiCellStyleManager* cell_style_manager) {
    if (cell->style.background_color != cell_style_manager->current_background_color) {
        cell_style_manager->current_background_color = cell->style.background_color;
        wprintf(L"\033[%dm", cell_style_manager->current_background_color);
    }
    if (cell->style.foreground_color != cell_style_manager->current_foreground_color) {
        cell_style_manager->current_foreground_color = cell->style.foreground_color;
        wprintf(L"\033[%dm", cell_style_manager->current_foreground_color);
    }
    if (cell->style.property != cell_style_manager->current_property) {
        cell_style_manager->current_property = cell->style.property;
        wprintf(L"\033[%dm", cell_style_manager->current_property);
    }

    wprintf(L"%lc", cell->character);
}
