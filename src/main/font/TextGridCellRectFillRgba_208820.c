#include "types.h"

extern void TextGridCellRectFill_208760(s32 a, s32 b, s32 c, s32 d, s32 e, s32 f, s32 g, s32 h, f32 *v);

void TextGridCellRectFillRgba_208820(s32 a, s32 b, s32 c, s32 d, s32 e, s32 f, s32 g, s32 h,
                  f32 x, f32 y, f32 z, f32 w)
{
    f32 v[4] = {0};

    v[0] = x;
    v[1] = y;
    v[2] = z;
    v[3] = w;
    TextGridCellRectFill_208760(a, b, c, d, e, f, g, h, v);
}
