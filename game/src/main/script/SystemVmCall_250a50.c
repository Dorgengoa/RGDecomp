/* rgp:protos */
#define RGP_SELF_SystemVmCall_250a50 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s32 D_00481F78;
extern s32 D_00481F7C;
extern u8 gSystemVm[];

s32 SystemVmCall_250a50(s32 p0, s32 p1, f32 fa0, f32 fa1, f32 fa2, f32 fa3, f32 fa4, f32 fa5, f32 fa6, f32 fa7)
{
    s32 r0;
    s32 r1;

    D_00481F78 = p1;
    r0 = ScriptVmRunEntry_176940(gSystemVm, p0);
    if (r0 == -1) {
        return 0;
    }
    if (r0 != 0) {
        D_00481F7C = p0;
        r1 = EventSysUpdate_26ac10();
    }
    return r0;
}
