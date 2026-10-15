#include "types.h"

extern s32 FontMeasureStringWidth_2773d0(void *, void *);

s32 MesWinGetStrVarWidth_277390(u8 *p, s32 i)
{
    if (i < 0) {
        return -1;
    }
    if (i >= 0x10) {
        return -1;
    }
    return FontMeasureStringWidth_2773d0(p, p + i * 32 + 0x195D);
}
