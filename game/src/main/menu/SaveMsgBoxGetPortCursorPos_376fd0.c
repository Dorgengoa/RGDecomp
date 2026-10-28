/* rgp:protos */
#define RGP_SELF_SaveMsgBoxGetPortCursorPos_376fd0 1
#include "port/game_protos.h"
#line 1
/* main s27m: CLOSED -- sp98 is a 4-byte out slot (frame 0xA0, not 0xC0) and
   UiGetWidgetPos_2910a0 takes (arg0, id): retail never writes $a0. */
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern u16 D_0047FB04;

#pragma divbyzerocheck on
void SaveMsgBoxGetPortCursorPos_376fd0(s32 arg0, s32 arg1, s32 *arg2, s32 *arg3) {
    s32 sp9C;
    s32 sp98;
    u8 sp50[0x40] __attribute__((aligned(16)));
    s32 temp_19;
    s32 temp_3;

    if (arg0 != 0) {
        UiGetWidgetPos_2910a0(arg0, D_0047FB04, (void *)arg2, (void *)arg3);
        temp_19 = UiGetWidgetTextHeight_28f3d0(arg0, D_0047FB04, 0);
        TextStyleInit_26c610(sp50);
        FontMeasureString_26daf0(sp50, SaveMenuMsgLookup_376b30(0x19), &sp9C, &sp98);
        *arg2 += sp9C;
        *arg3 += (temp_19 / 3) * (arg1 + 2);
        temp_3 = *arg2 - 4;
        *arg2 = temp_3;
        *arg2 = temp_3 - 0x16;
        *arg3 -= 0xF;
    }
}
