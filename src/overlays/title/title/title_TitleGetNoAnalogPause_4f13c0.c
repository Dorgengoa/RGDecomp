#include "types.h"

/* title.bin overlay, 0x004F13C0 -- lw $2, -0xEDC($28) */

extern s32 D_00484294;

s32 title_TitleGetNoAnalogPause_4f13c0(void)
{
    return D_00484294;
}
