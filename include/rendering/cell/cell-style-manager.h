#pragma once

#include "types/color.h"
#include "rendering/cell/cell.h"

typedef struct CellStyleManager {
    ForegroundColor current_foreground_color;
    BackgroundColor current_background_color;
    CellProperty current_property;
} CellStyleManager;

CellStyleManager ttyui_cell_style_manager_create();
void ttyui_cell_style_manager_switch_current_foreground_color(CellStyleManager* cell_style_manager, ForegroundColor foreground_color);
void ttyui_cell_style_manager_switch_current_background_color(CellStyleManager* cell_style_manager, BackgroundColor background_color);
void ttyui_cell_style_manager_switch_current_property(CellStyleManager* cell_style_manager, CellProperty property);
