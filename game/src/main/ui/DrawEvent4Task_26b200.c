/* rgp:protos */
#define RGP_SELF_DrawEvent4Task_26b200 1
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

extern s32 D_0048206C;
extern u8 D_00482070;

void DrawEvent4Task_26b200(void)
{
    s32 r0;
    s32 l1;
    s32 t0;
    s32 r2;
    s32 rv4;
    s32 t1;
    s32 r3;
    u8 t2;
    s32 r5;

    r0 = GetCurrentScene_1f5be0();
    l1 = 0;
    do {
        t0 = D_0048206C;
        r2 = MenuWinGetDrawLayer_26c280((t0 + (((l1 << 3) - l1) << 5)));
        rv4 = r2;
        if (r2 == 3) {
            t1 = D_0048206C;
            r3 = (MenuWinUpdate_26bfe0((t1 + (((l1 << 3) - l1) << 5)), r0), (s32)0);
            rv4 = r3;
        }
        l1 = (l1 + 1);
    } while (l1 < 8);
    t2 = D_00482070;
    if (t2 != 0) {
        r5 = (PauseReasonDrawMaybe_2f5c40(7), (s32)0);
        return;
    }
}
