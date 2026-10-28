/* rgp:protos */
#define RGP_SELF_ScriptOpSkipArgs_3da0e0 1
#include "port/game_protos.h"
#line 1
#include "types.h"



/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x1];
    u8 m01;
};

struct Obj0 *ScriptOpSkipArgs_3da0e0(s32 p0, s32 p1, s32 p2, struct Obj0 *p3)
{
    struct Obj0 * rv2;
    u8 t0;
    struct Obj0 * rv1;
    struct Obj0 * rv0;

    if (p3 == 0) {
        rv2 = 0;
    } else {
        t0 = p3->m01;
        rv1 = (struct Obj0 *)((u8 *)p3 + 2);
        if (t0 > 0) {
            rv0 = (struct Obj0 *)((u8 *)p3 + 2);
            if (t0 < 8) {
                rv0 = (struct Obj0 *)((u8 *)(struct Obj0 *)((u8 *)p3 + 2) + t0);
            }
            rv1 = rv0;
        }
        rv2 = rv1;
    }
    return rv2;
}
