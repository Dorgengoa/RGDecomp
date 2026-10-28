/* rgp:protos */
#define RGP_SELF_WorldSubsysSetupGama_406bd0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
extern s32 memset(s32, s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s32 D_004658D0;

struct Obj0;

struct Obj0 {
    u8 pad000[0x4];
    s32 m04;
    s32 m08;
    s32 m0C;
    s32 m10;
    s16 m14;
    u8 pad016[0x2];
    s32 m18;
};

s32 WorldSubsysSetupGama_406bd0(struct Obj0 *p0)
{
    s32 t0;
    s32 rv1;
    s32 t1;
    s32 t2;
    s32 t3;
    s32 r2;
    s32 rv7;
    s32 r3;
    s32 t4;
    s32 t5;
    s32 r4;
    s32 rv6;
    s32 r5;

    t0 = p0->m0C;
    if (t0 != 0) {
        t1 = p0->m08;
        WorldSubsysSortLists_406e20(t0, t1);
        t2 = p0->m04;
        rv1 = t2;
    } else {
        t3 = p0->m04;
        rv1 = t3;
    }
    r2 = ((s32)MemStackNew_14e0b0(0x36, rv1));
    p0->m10 = r2;
    if (r2 == 0) {
        rv7 = 0;
    } else {
        r3 = ((s32)memset(r2, 0, 0x36));
        p0->m14 = 0;
        t4 = D_004658D0;
        t5 = p0->m04;
        r4 = ((s32)MemStackNew_14e0b0((((t4 << 3) - t4) << 2), t5));
        p0->m18 = r4;
        rv6 = 1;
        if (r4 == 0) {
            rv6 = 0;
        } else {
            r5 = ((s32)memset(r4, 0, (((t4 << 3) - t4) << 2)));
            rv6 = 1;
        }
        rv7 = rv6;
    }
    return rv7;
}
