/* rgp:protos */
#define RGP_SELF_EvCmdEventMesWinSetStyle_245a80 1
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

extern struct Obj0 * gEventContext;

struct Obj0;
struct Obj1;

struct Obj0 {
    u8 pad000[0x4];
    struct Obj1 *m04;
};

struct Obj1 {
    u8 pad000[0x42C];
    s32 m42C;
};

s32 EvCmdEventMesWinSetStyle_245a80(s32 p0)
{
    struct Obj0 * t0;
    struct Obj1 * t1;
    s32 t2;
    s32 rv3;
    s32 r0;
    s32 r2;

    t0 = gEventContext;
    t1 = gEventContext->m04;
    t2 = gEventContext->m04->m42C;
    rv3 = 1;
    if (t2 == 0) {
        rv3 = 0;
    } else {
        r0 = ScriptGetInt_2490f0(p0);
        MesWinSetStyle_276d60(t2, r0);
        r2 = (MesWinSetSeEnabled_272b50(t2, 0), (s32)0);
        rv3 = 1;
    }
    return rv3;
}
