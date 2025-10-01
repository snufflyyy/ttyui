#pragma once

#include "types/color.h"
struct TtyuiCellStyleManager;

#include <wchar.h>

typedef enum TtyuiCellProperty {
    TTYUI_CELL_PROPERTY_NONE = 0,
    TTYUI_CELL_PROPERTY_BOLD = 1,
    TTYUI_CELL_PROPERTY_DIM = 2,
    TTYUI_CELL_PROPERTY_ITALIC = 3,
    TTYUI_CELL_PROPERTY_UNDERLINE = 4,
    TTYUI_CELL_PROPERTY_BLINKING = 5,
    TTYUI_CELL_PROPERTY_REVERSE = 7,
    TTYUI_CELL_PROPERTY_HIDDEN = 8,
    TTYUI_CELL_PROPERTY_STRIKETHROUGH = 9,
} TtyuiCellProperty;

typedef struct TtyuiCellStyle {
    TtyuiBackgroundColor background_color;
    TtyuiForegroundColor foreground_color;
    TtyuiCellProperty property;
} TtyuiCellStyle;

typedef struct TtyuiCell {
    wchar_t character;
    TtyuiCellStyle style;
} TtyuiCell;

TtyuiCell ttyui_cell_create();
void ttyui_cell_print(TtyuiCell* cell, struct TtyuiCellStyleManager* cell_style_manager);
