#include "types.h"

extern void *D_00484104;
extern void TextEntryPaletteTextStyle_433490(void *p, s32 a, s32 b, s32 c, s32 d, s32 e);

s32 TextEntryPaletteTextStyleDrawCb_432ac0(s32 a, s32 b, s32 c, s32 d, s32 e)
{
    if (D_00484104 != 0) TextEntryPaletteTextStyle_433490(D_00484104, a, b, c, d, e);
    return 1;
}
