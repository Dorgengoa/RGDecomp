/* rgp:protos */
#define RGP_SELF_MenuPartyCmdRowDim_29c390 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
extern f32 D_0047D288;
extern u16 D_0047EC10;
extern u16 D_0047EC00;

s32 MenuPartyCmdRowDim_29c390(void *arg0,s32 arg1, s64 arg2)
{
    if (*(s8 *)((u8 *)MenuGetCursorPos_29fae0((void *)arg0) + 0x1) == 0) {
        UiSetWidgetColor_2905b0(*(s32 *)((u8 *)arg0 + 0x4C4),
            *(u16 *)((u8 *)&D_0047EC00 + ((s16)arg2 * 2)),
            D_0047D288, D_0047D288, D_0047D288, 1.0f);
    } else {
        UiSetWidgetColor_2905b0(*(s32 *)((u8 *)arg0 + 0x4C4),
            *(u16 *)((u8 *)&D_0047EC10 + ((s16)arg2 * 2)),
            D_0047D288, D_0047D288, D_0047D288, 1.0f);
    }
    return 0;
}
