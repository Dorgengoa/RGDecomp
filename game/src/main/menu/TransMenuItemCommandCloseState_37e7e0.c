/* rgp:protos */
#define RGP_SELF_TransMenuItemCommandCloseState_37e7e0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern f32 D_0047D984;
extern s32 D_0048470C;
extern s32 D_00484710;

s32 TransMenuItemCommandCloseState_37e7e0(s32 p0, s32 p1)
{
    s32 t0;
    f32 t1;
    s32 t2;
    f32 t3;
    s32 l2;
    s32 t4;
    f32 t5;
    s32 t6;

    if (p1 != 0) {
        t0 = D_00484710;
        t1 = D_0047D984;
        UiFadeWidgetAlpha_290690(t0, 0x760A, 0.0f, t1, -1.0f);
        t2 = D_00484710;
        t3 = D_0047D984;
        UiFadeWidgetAlpha_290690(t2, 0x7609, 0.0f, t3, -1.0f);
        l2 = 0;
        do {
            t4 = D_00484710;
            t5 = D_0047D984;
            UiFadeWidgetAlpha_290690(t4, ((l2 + 0x7652) & 0xFFFF), 0.0f, t5, -1.0f);
            l2 = (l2 + 1);
        } while (l2 < 6);
    }
    t6 = D_0048470C;
    StateMachineSetState_28ede0(t6, 0x20, 0);
    return 1;
}
