/* rgp:protos */
#define RGP_SELF_EvCmdTaskApplyPresetMaybe_244320 1
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

extern u8 D_0045EA80[];

struct Obj0;
struct Obj1;

struct Obj0 {
    u8 pad000[0xC];
    struct Obj1 *m0C;
};

struct Obj1 {
    u8 pad000[0x1C];
    s16 m1C;
};

s32 EvCmdTaskApplyPresetMaybe_244320(s32 p0, s32 p1)
{
    s32 rv4;
    s32 r0;
    s32 r1;
    struct Obj0 *r2;
    struct Obj1 * t0;
    s16 t1;
    s32 r3;

    rv4 = 1;
    if (p1 != 1) {
        rv4 = 0;
    } else {
        r0 = ScriptGetInt_2490f0(p0);
        r1 = (TaskApplyPresetMaybe_27af70(r0), (s32)0);
        r2 = GetGameData_1fede0();
        t0 = r2->m0C;
        t1 = r2->m0C->m1C;
        if (t1 == 0) {
            r3 = TaskSetEnabled_27c2a0(0, D_0045EA80);
        }
        rv4 = 1;
    }
    return rv4;
}
