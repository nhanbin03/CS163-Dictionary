#ifndef COLORPALETTES_APPCOLORPALETTE_H
#define COLORPALETTES_APPCOLORPALETTE_H

#include "raylib.h"

namespace AppColor {
    const Color BACKGROUND_1 = GetColor(0x1E1E1EFF);
    const Color BACKGROUND_2 = GetColor(0x252525FF);
    const Color BACKGROUND_3 = GetColor(0x2D2D2DFF);
    const Color BACKGROUND_4 = GetColor(0x3C3C3CFF);

    const Color TEXT = GetColor(0xC4C4C4FF);
    const Color TEXT_ACCENT = GetColor(0xFFFFFFFF);

    const Color PRIMARY = GetColor(0x0C8CE9FF);

    const Color CODE = GetColor(0x9AA0A6FF);
    const Color CODE_ACCENT = GetColor(0xD2E3FCFF);
    const Color CODE_ACCENT_BACKGROUND = GetColor(0x394456FF);
} // namespace AppColor

#endif // COLORPALETTES_APPCOLORPALETTE_H
