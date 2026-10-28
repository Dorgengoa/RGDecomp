/* rgp:protos */
#define RGP_SELF_SeventhMysteryNextQuestion_394610 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/

extern f32 D_0047D7C8;
extern u8 D_00483470;
extern s16 D_0048349C;
extern u8 D_004E9550[0x400];

s32 SeventhMysteryNextQuestion_394610(s32 arg0, s32 arg1)
{
    s32 i;

    if (arg1 != 0) {
        i = 0;
        do {
            UiFadeWidgetAlpha_290690(D_004E9550, (i + 6) & 0xFFFF, 0.0f, D_0047D7C8, -1.0f);
            i += 1;
        } while (i < 4);
        UiFadeWidgetAlpha_290690(D_004E9550, 4, 0.0f, D_0047D7C8, -1.0f);
    }
    if (++D_0048349C > 6) {
        StateMachineSetState_28ede0(&D_00483470, 0x7537, 0);
    } else {
        StateMachineSetState_28ede0(&D_00483470, 0x7532, 0);
    }
    return 1;
}
