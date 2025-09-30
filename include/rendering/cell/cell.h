#pragma once

#include "types/color.h"
struct CellStyleManager;

#include <wchar.h>

typedef enum CellProperty {
    TTYUI_CELL_PROPERTY_NONE = 0,
    TTYUI_CELL_PROPERTY_BOLD = 1,
    TTYUI_CELL_PROPERTY_DIM = 2,
    TTYUI_CELL_PROPERTY_ITALIC = 3,
    TTYUI_CELL_PROPERTY_UNDERLINE = 4,
    TTYUI_CELL_PROPERTY_BLINKING = 5,
    TTYUI_CELL_PROPERTY_REVERSE = 7,
    TTYUI_CELL_PROPERTY_HIDDEN = 8,
    TTYUI_CELL_PROPERTY_STRIKETHROUGH = 9,
} CellProperty;

typedef struct CellStyle {
    BackgroundColor background_color;
    ForegroundColor foreground_color;
    CellProperty property;
} CellStyle;

typedef struct Cell {
    wchar_t character;
    CellStyle style;
} Cell;

Cell ttyui_cell_create();
void ttyui_cell_print(Cell* cell, struct CellStyleManager* cell_style_manager);
