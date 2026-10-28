/* rgp:protos */
#define RGP_SELF_GoTitleMenuUpdate_39bf70 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s32 D_00483610;
extern s16 D_00483628;
extern s32 D_00483640;
extern u8 D_004E9660[];

s32 GoTitleMenuUpdate_39bf70(s32 p0, s32 p1)
{
    s16 t0;
    s32 t1;
    s32 t2;

    t0 = D_00483628;
    if (t0 == 0) {
        t1 = D_00483640;
        return t1;
    }
    if (((((s64)t0) << 0x30) >> 0x30) == 1) {
        D_00483628 = 2;
        StateMachineSetState_28ede0(&D_00483610, 0x7152, 1);
    }
    UiUpdateWidgets_2913a0(D_004E9660);
    StateMachineUpdate_28ed70(&D_00483610);
    t2 = D_00483640;
    return t2;
}
