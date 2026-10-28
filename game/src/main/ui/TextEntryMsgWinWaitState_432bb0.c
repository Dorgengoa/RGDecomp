/* rgp:protos */
#define RGP_SELF_TextEntryMsgWinWaitState_432bb0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern u8 D_004B2570[];

struct Obj0;

struct Obj0 {
    u8 pad000[0x4];
    s32 m04;
};

s32 TextEntryMsgWinWaitState_432bb0(struct Obj0 *p0, s32 p1)
{
    s32 t0;
    s32 r0;
    s32 t1;
    s32 r1;
    s32 t2;

    if (p1 != 0) {
        t0 = p0->m04;
        r0 = UiEntryListSelectByTag_28ea90(t0, 0x6D63, 0);
    }
    t1 = p0->m04;
    r1 = MenuGridCursorInput_28e170(t1, D_004B2570, 0, 0);
    t2 = p0->m04;
    UiEntryListGetCurrentData_28ec60(t2);
    if ((u32)(r1 + -1) < 2) {
        TextEntrySetState_434410(p0, 0x6D6C, 0);
    }
    return 1;
}
