#include "rendering/cell/cell-style-manager.h"
#include "rendering/cell/cell.h"
#include "types/color.h"

inline CellStyleManager ttyui_cell_style_manager_create() {
    return (CellStyleManager) { TTYUI_COLOR_FOREGROUND_DEFAULT, TTYUI_COLOR_BACKGROUND_DEFAULT, TTYUI_CELL_PROPERTY_NONE };
}
