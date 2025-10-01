#pragma once

#include "types/color.h"
#include "rendering/cell/cell.h"

typedef struct TtyuiCellStyleManager {
    TtyuiForegroundColor current_foreground_color;
    TtyuiBackgroundColor current_background_color;
    TtyuiCellProperty current_property;
} TtyuiCellStyleManager;

TtyuiCellStyleManager ttyui_cell_style_manager_create();
void ttyui_cell_style_manager_switch_current_foreground_color(TtyuiCellStyleManager* cell_style_manager, TtyuiForegroundColor foreground_color);
void ttyui_cell_style_manager_switch_current_background_color(TtyuiCellStyleManager* cell_style_manager, TtyuiBackgroundColor background_color);
void ttyui_cell_style_manager_switch_current_property(TtyuiCellStyleManager* cell_style_manager, TtyuiCellProperty property);
