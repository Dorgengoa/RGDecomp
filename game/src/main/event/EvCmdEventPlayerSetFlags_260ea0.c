/* rgp:protos */
#define RGP_SELF_EvCmdEventPlayerSetFlags_260ea0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct E8W { u8 b[8]; } E8W;

/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern struct Obj0 * D_00482040;

struct Obj0;

struct Obj0 {
    u8 pad000[0xA60];
    s32 mA60;
};

s32 EvCmdEventPlayerSetFlags_260ea0(s32 p0, s32 p1)
{
    struct Obj0 * t0;
    s32 rv3;
    s32 r0;
    s32 r1;
    s32 rv2;
    struct Obj0 * t1;
    s32 t2;
    struct Obj0 * t3;
    s32 t4;
    E8W *q;

    q = (E8W *)p0;
    if (p1 != 2) {
        return 0;
    }
    t0 = D_00482040;
    rv3 = 1;
    if (t0 == 0) {
        rv3 = 0;
    } else {
        r0 = ScriptGetInt_26a2a0((s32)q++);
        r1 = ScriptGetInt_26a2a0((s32)q);
        if (r1 != 0) {
            t1 = D_00482040;
            t2 = D_00482040->mA60;
            D_00482040->mA60 = (t2 | r0);
            rv2 = (t2 | r0);
        } else {
            t3 = D_00482040;
            t4 = D_00482040->mA60;
            D_00482040->mA60 = (t4 & ~r0);
            rv2 = (t4 & ~r0);
        }
        rv3 = 1;
    }
    return rv3;
}
