/* rgp:protos */
#define RGP_SELF_GsPktCommit_13f190 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    s32 m00;
    u8 pad004[0xE4];
    s32 mE8;
    s32 mEC;
    u8 pad0F0[0x4];
    s32 mF4;
};

void GsPktCommit_13f190(struct Obj0 *p0)
{
    s32 t0;
    s32 t1;
    s32 t2;
    s32 rv0;
    s32 rv1;
    s32 t3;

    t0 = p0->mE8;
    if (t0 == 0) {
        t1 = p0->mF4;
        t2 = p0->mEC;
        rv0 = (t1 - t2);
        rv1 = ((t1 - t2) >> 4);
        if ((t1 - t2) < 0) {
            rv0 = ((t1 - t2) + 0xF);
            rv1 = (((t1 - t2) + 0xF) >> 4);
        }
        t3 = p0->m00;
        MemStackAllocQw_14d950(t3, rv1);
        return;
    }
}
