/* rgp:protos */
#define RGP_SELF_TargetMngGetTargetRef_320820 1
#include "port/game_protos.h"
#line 1
#include "types.h"



/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    s32 m00;
    u8 pad004[0x4];
    s32 m08;
};

struct Obj0 *TargetMngGetTargetRef_320820(struct Obj0 *p0)
{
    s32 t0;
    s32 t1;

    t0 = p0->m08;
    if (t0 == 0) {
        return (struct Obj0 *)0;
    }
    t1 = p0->m00;
    if (t1 != 1) {
        return (struct Obj0 *)0;
    }
    return (struct Obj0 *)((u8 *)p0 + 0xC0);
}
