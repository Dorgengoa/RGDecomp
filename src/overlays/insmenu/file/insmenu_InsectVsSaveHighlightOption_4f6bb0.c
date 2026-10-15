#include "types.h"
/* insmenu 0x004F6BB0 -- the same shape as the matched title_TitleLoadHighlightOption_4ede30:
 * three ADJACENT gp s16 globals copied into a 3-element frame array, all
 * loads before all stores with one named local per load in LISTING order.
 * They are three separate globals, not a block copy. */
extern s16 D_00480468;
extern s16 D_0048046A;
extern s16 D_0048046C;
extern void func_37B5D0(s16 a, s16 *buf, s32 n);

void insmenu_InsectVsSaveHighlightOption_4f6bb0(s16 a)
{
    s16 buf[3];
    s16 x;
    s16 y;
    s16 z;

    x = D_00480468;
    y = D_0048046A;
    z = D_0048046C;
    buf[0] = x;
    buf[1] = y;
    buf[2] = z;
    func_37B5D0(a, buf, 0x88C6);
}
